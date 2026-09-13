/*
 * lwIP sizing for riscv/esp32c3db.
 *
 * Copyright (C) 2026 Samuel Price <thesamprice@gmail.com>
 *
 * Every default in rtemslwip/include/lwipopts.h is #ifndef-guarded, and the
 * defaults were chosen for parts with external DRAM.  Left alone they ask for
 * more memory than this chip has:
 *
 *   MEM_SIZE          2 MiB
 *   PBUF_POOL_SIZE    512, of PBUF_POOL_BUFSIZE 1600  =  800 KiB
 *
 * against 384 KiB of internal SRAM, of which the BSP's RAM region is 320 KiB
 * and about 218 KiB is free once RTEMS and the WiFi libraries have taken
 * theirs.  That is not a tuning difference; the defaults cannot link here.
 *
 * The ESP32-C3 has no external RAM interface -- SOC_SPIRAM_SUPPORTED is not
 * defined for it -- so there is no configuration in which the defaults fit.
 * The 4 MiB of SPI flash does not help: these are all live buffers.
 *
 * The numbers below are a starting point derived from the part, not from
 * measured traffic.  They should be revisited against a real workload; what
 * matters for now is that each says what it is paying for.
 */

#ifndef RTEMSLWIP_ESP32C3_LWIPBSPOPTS_H
#define RTEMSLWIP_ESP32C3_LWIPBSPOPTS_H

/*
 * The receive pool.  This is the largest single item and the one that decides
 * how many frames can be in flight before the driver starts dropping.
 *
 * 1600 covers a 1500-byte MTU plus the Ethernet header and alignment, which is
 * what the WiFi driver hands up; 24 of them is 37.5 KiB.  The WiFi libraries
 * have their own RX buffers in front of this -- CONFIG_ESP_WIFI_*_RX_BUFFER_NUM
 * in the port's sdkconfig.h -- so this pool is the second queue, not the first.
 */
#define PBUF_POOL_SIZE     24
#define PBUF_POOL_BUFSIZE  1600

/*
 * The heap lwIP allocates transmit buffers and netbufs from.  32 KiB against
 * the 2 MiB default.
 */
#define MEM_SIZE           ( 32 * 1024 )

/*
 * The pools, scaled to a part that will hold a handful of connections rather
 * than hundreds.  An ESPHome node is one API client, mDNS, and perhaps a
 * couple of sensors reporting; MicroPython is whatever the script opens.
 */
#define MEMP_NUM_PBUF             16
#define MEMP_NUM_FRAG_PBUF         8
#define MEMP_NUM_NETCONN           8
#define MEMP_NUM_TCP_PCB           8
#define MEMP_NUM_TCP_PCB_LISTEN    4
#define MEMP_NUM_TCP_SEG          24
#define MEMP_NUM_UDP_PCB           6

/*
 * Four segments rather than eight in each direction: 8 * TCP_MSS is 11.6 KiB
 * per socket per direction, which is more than this part should commit to one
 * connection.  It costs throughput on a long fat link, which a 2.4 GHz station
 * talking to a local access point is not.
 */
#define TCP_SND_BUF        ( 4 * TCP_MSS )
#define TCP_WND            ( 4 * TCP_MSS )

/*
 * The send queue has to be set with TCP_SND_BUF, not left at its default.
 *
 * lwIP derives it as 16 * TCP_SND_BUF / TCP_MSS, which with the buffer above
 * is 64 segments -- more than MEMP_NUM_TCP_SEG, and lwIP's own sanity check in
 * core/init.c refuses to build rather than let the queue outrun the pool.  It
 * is right to: the failure would otherwise be a transmit stall under load.
 *
 * 4 * TCP_SND_BUF / TCP_MSS is 16, comfortably inside the 24 segments above
 * and still four times the two lwIP documents as the floor.
 */
#define TCP_SND_QUEUELEN   ( ( 4 * TCP_SND_BUF ) / TCP_MSS )

/*
 * Needed by esp_wifi_internal_set_sta_ip(), which tells the WiFi libraries the
 * station's address so they can answer ARP while the CPU sleeps.  rtems-lwip
 * leaves it off by default; the ESP32-C3's only interface is the one that
 * wants it.
 */
#define LWIP_NETIF_STATUS_CALLBACK  1

#endif /* RTEMSLWIP_ESP32C3_LWIPBSPOPTS_H */
