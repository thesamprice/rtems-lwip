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
 * The two largest items are sized against what they cost in .bss rather than
 * against a guess, because on this part the whole margin is 14 KiB and a
 * static buffer is taken from the same 272 KiB the WiFi libraries allocate
 * from.  rtems-esphome#121 has the measurement.  Two identities are worth
 * having in front of you before changing a number here, both confirmed
 * against riscv-rtems7-nm on the built liblwip.a:
 *
 *   memp_memory_PBUF_POOL_base = PBUF_POOL_SIZE * ( sizeof( struct pbuf )
 *                                                   + PBUF_POOL_BUFSIZE )
 *   ram_heap                   = MEM_SIZE + 2 * sizeof( struct mem )
 *
 * sizeof( struct pbuf ) is 16 and sizeof( struct mem ) is 6 here; MEM_ALIGNMENT
 * is lwIP's default of 1, so neither expression carries any rounding.
 */

#ifndef RTEMSLWIP_ESP32C3_LWIPBSPOPTS_H
#define RTEMSLWIP_ESP32C3_LWIPBSPOPTS_H

/*
 * The receive pool.  This is the largest single item and the one that decides
 * how many frames can be in flight before the driver starts dropping.
 *
 * A buffer has to hold one whole frame, because rtems_esp_netif_input() asks
 * for pbuf_alloc( PBUF_RAW, len, PBUF_POOL ) and a len larger than this is
 * answered with a chain rather than a refusal -- which works, and quietly
 * costs two pool entries per frame.  RTEMS_ESP_NETIF_FRAME_MAX is 1518 and
 * the netif's MTU is 1500, so 1520 is that frame rounded up to 16.  The 1600
 * it replaces was never a frame size; it was the rtems-lwip default.
 *
 * Twelve of them is 18 KiB.  What has to fit at once is a full TCP receive
 * window -- TCP_WND below is four segments -- plus whatever is queued in the
 * tcpip mailbox behind it, so twelve is about three times the depth a single
 * station can put in flight.  The WiFi libraries have their own RX buffers in
 * front of this -- CONFIG_ESP_WIFI_*_RX_BUFFER_NUM in the port's sdkconfig.h
 * -- so this pool is the second queue, not the first.
 *
 * A pool that is too small does not report an error.  It drops frames, and
 * the radio goes quiet under load.  lwIP counts both ends of that for us:
 * lwip_stats.memp[ MEMP_PBUF_POOL ]->err is the refusal count and ->max the
 * high-water mark, and MEMP_STATS is on by default.  Check them, not the
 * absence of a complaint, before changing this number again.
 */
#define PBUF_POOL_SIZE     12
#define PBUF_POOL_BUFSIZE  1520

/*
 * The heap lwIP allocates transmit buffers and netbufs from.  16 KiB against
 * the 2 MiB default.
 *
 * It holds unacknowledged transmit data and nothing else that is large: one
 * connection's TCP_SND_BUF is four segments, so about 7 KiB of pbufs with
 * their headers, and DHCP, DNS and the mDNS responder each hold one packet at
 * a time.  16 KiB is roughly twice that, and lwip_stats.mem.max says on any
 * run how much of it was ever used.
 *
 * MEM_LIBC_MALLOC is deliberately left off.  Turning it on would delete this
 * buffer entirely and hand lwIP the RTEMS heap instead, which is 16 KiB more
 * for everyone and one pool to run out of rather than two.  The reason not to
 * is what runs out of the other one: the WiFi libraries answer ESP_ERR_NO_MEM
 * by scanning zero networks, so a shared heap turns an lwIP burst into a radio
 * that appears dead.  The wall between them is what makes "which heap ran out"
 * answerable at all today.  Revisit it once lwip_stats.mem.max has been read
 * off a real workload; note that it would not shrink the pools above, which
 * stay static unless MEMP_MEM_MALLOC is also set.
 */
#define MEM_SIZE           ( 16 * 1024 )

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
