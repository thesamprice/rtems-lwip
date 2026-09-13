/*
 * Copyright (C) 2023 On-Line Applications Research Corporation (OAR)
 * Written by Kinsey Moore <kinsey.moore@oarcorp.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include <lwipconfig.h>

/* Critical items that all BSPs must use for full functionality */
#define SYS_LIGHTWEIGHT_PROT 1
#define NO_SYS 0
#define LWIP_SOCKET 1
#define SO_REUSE 1
#define LWIP_COMPAT_SOCKETS 1
#define LWIP_NETCONN 1
#define LWIP_NETIF_LOOPBACK 1 /* Required for socketpair implementation */
#define LWIP_NETIF_API 1
#define LWIP_TIMEVAL_PRIVATE 0
#define LWIP_CALLBACK_API 1
#define NO_SYS_NO_TIMERS 1
#define LWIP_COMPAT_MUTEX 0
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 1

#include <lwipbspopts.h>

/* Sane defaults that the configuration or BSP can override */

#ifndef ARP_QUEUEING
#define ARP_QUEUEING 1
#endif

#ifndef ARP_TABLE_SIZE
#define ARP_TABLE_SIZE 10
#endif

#ifndef CHECKSUM_CHECK_IP
#define CHECKSUM_CHECK_IP 1
#endif

#ifndef CHECKSUM_CHECK_TCP
#define CHECKSUM_CHECK_TCP 1
#endif

#ifndef CHECKSUM_CHECK_UDP
#define CHECKSUM_CHECK_UDP 1
#endif

#ifndef CHECKSUM_GEN_IP
#define CHECKSUM_GEN_IP 1
#endif

#ifndef CHECKSUM_GEN_TCP
#define CHECKSUM_GEN_TCP 1
#endif

#ifndef CHECKSUM_GEN_UDP
#define CHECKSUM_GEN_UDP 1
#endif

#ifndef CONFIG_LINKSPEED_AUTODETECT
#define CONFIG_LINKSPEED_AUTODETECT 1
#endif

#ifndef DEFAULT_ACCEPTMBOX_SIZE
#define DEFAULT_ACCEPTMBOX_SIZE 5
#endif

#ifndef DEFAULT_TCP_RECVMBOX_SIZE
#define DEFAULT_TCP_RECVMBOX_SIZE 20
#endif

#ifndef DEFAULT_UDP_RECVMBOX_SIZE
#define DEFAULT_UDP_RECVMBOX_SIZE 20
#endif

#ifndef LWIP_DHCP_DOES_ACD_CHECK
#define LWIP_DHCP_DOES_ACD_CHECK 1
#endif

#ifndef ICMP_TTL
#define ICMP_TTL 255
#endif

#ifndef IP_DEFAULT_TTL
#define IP_DEFAULT_TTL 255
#endif

#ifndef IP_FORWARD
#define IP_FORWARD 0
#endif

#ifndef IP_FRAG
#define IP_FRAG 1
#endif

#ifndef IP_FRAG_MAX_MTU
#define IP_FRAG_MAX_MTU 1500
#endif

#ifndef IP_OPTIONS
#define IP_OPTIONS 1
#endif

#ifndef IP_OPTIONS_ALLOWED
#define IP_OPTIONS_ALLOWED 0
#endif

#ifndef IP_REASS_BUFSIZE
#define IP_REASS_BUFSIZE 5760
#endif

#ifndef IP_REASSEMBLY
#define IP_REASSEMBLY 1
#endif

#ifndef LWIP_ARP
#define LWIP_ARP 1
#endif

#ifndef LWIP_AUTOIP
#define LWIP_AUTOIP 1
#endif

#ifndef LWIP_CHKSUM_ALGORITHM
#define LWIP_CHKSUM_ALGORITHM 3
#endif

#ifndef LWIP_DHCP
#define LWIP_DHCP 1
#endif

#ifndef LWIP_DHCP_AUTOIP_COOP
#define LWIP_DHCP_AUTOIP_COOP ((LWIP_DHCP) && (LWIP_AUTOIP))
#endif

#ifndef LWIP_DNS
#define LWIP_DNS 1
#endif

#ifndef LWIP_IPV4
#define LWIP_IPV4 1
#endif

#ifndef LWIP_IPV6
#define LWIP_IPV6 1
#endif

#ifndef LWIP_TCP
#define LWIP_TCP 1
#endif

#ifndef LWIP_UDP
#define LWIP_UDP 1
#endif

#ifndef MEMP_NUM_FRAG_PBUF
#define MEMP_NUM_FRAG_PBUF 256
#endif

#ifndef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN 16
#endif

#ifndef MEMP_NUM_PBUF
#define MEMP_NUM_PBUF 96
#endif

#ifndef MEMP_NUM_TCP_PCB
#define MEMP_NUM_TCP_PCB 32
#endif

#ifndef MEMP_NUM_TCP_PCB_LISTEN
#define MEMP_NUM_TCP_PCB_LISTEN 8
#endif

#ifndef MEMP_NUM_TCP_SEG
#define MEMP_NUM_TCP_SEG 256
#endif

#ifndef MEMP_NUM_UDP_PCB
#define MEMP_NUM_UDP_PCB 16
#endif

#ifndef MEMP_SEPARATE_POOLS
#define MEMP_SEPARATE_POOLS 1
#endif

#ifndef MEM_SIZE
#define MEM_SIZE 2 * 1024 * 1024
#endif

#ifndef PBUF_LINK_HLEN
#define PBUF_LINK_HLEN 16
#endif

#ifndef PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE 1600
#endif

#ifndef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE 512
#endif

#ifndef TCP_FAST_INTERVAL
#define TCP_FAST_INTERVAL 250
#endif

#ifndef TCPIP_MBOX_SIZE
#define TCPIP_MBOX_SIZE 20
#endif

#ifndef TCP_MAXRTX
#define TCP_MAXRTX 12
#endif

#ifndef TCP_MSS
#define TCP_MSS 1576
#endif

#ifndef TCP_OVERSIZE
#define TCP_OVERSIZE TCP_MSS
#endif

#ifndef TCP_QUEUE_OOSEQ
#define TCP_QUEUE_OOSEQ 1
#endif

#ifndef TCP_SLOW_INTERVAL
#define TCP_SLOW_INTERVAL 500
#endif

#ifndef TCP_SND_BUF
#define TCP_SND_BUF (8 * TCP_MSS)
#endif

#ifndef TCP_SND_QUEUELEN
#define TCP_SND_QUEUELEN 16 * TCP_SND_BUF / TCP_MSS
#endif

#ifndef TCP_SYNMAXRTX
#define TCP_SYNMAXRTX 4
#endif

#ifndef TCP_TMR_INTERVAL
#define TCP_TMR_INTERVAL 250
#endif

#ifndef TCP_TTL
#define TCP_TTL 255
#endif

#ifndef TCP_WND
#define TCP_WND (8 * TCP_MSS)
#endif

#ifndef UDP_TTL
#define UDP_TTL 255
#endif

/*
 * Multicast DNS.
 *
 * The responder is available -- its sources are imported and compiled -- but
 * off, which is lwip's own default.  Two things about that are worth knowing,
 * because the obvious next step is to turn it on and both bear on whether to.
 *
 * The original reason for leaving it off has gone.  Joining a multicast group
 * goes through the Xilinx port's MAC filter update, and on
 * arm/xilinx_zynq_a9_qemu the interface did not transmit again afterwards, so
 * enabling this would have broken every user of that BSP.  That defect is
 * fixed in the two commits before this one.
 *
 * What replaces it: with the responder enabled, mdns_resp_add_netif() and
 * mdns_resp_announce() both succeed and correctly formed packets do reach the
 * wire -- 299 of them to 224.0.0.251:5353 in one measured run -- but every one
 * is a probe.  The responder never finishes probing and never announces, so it
 * emits at roughly 23 packets per second for as long as it runs.  Defaulting
 * that on would give every user of this library a packet storm.
 *
 * Note also that this is a decision for whoever builds the library, not for an
 * application: liblwip.a is built once and installed, so an application cannot
 * turn a compile-time option on afterwards.  Making it selectable wants a
 * build option rather than a define here.
 *
 * The block below only arranges that a build which *does* define
 * LWIP_MDNS_RESPONDER gets the four options mdns.c requires, rather than the
 * three #errors and one silent misconfiguration it would otherwise meet.
 * MEMP_NUM_SYS_TIMEOUT being too small is not the cause of the probe loop --
 * eight extra slots changes nothing.
 */
/*
 * On, which is not lwip's default.  It has to be decided here: liblwip.a is
 * built once and installed, so an application cannot turn a compile-time
 * option on afterwards.  Making it selectable properly wants a build option
 * rather than a define, which is worth doing and is not done.
 *
 * Both reasons it was previously off have gone.  The Xilinx driver no longer
 * loses its transmit path on a multicast join, and the responder no longer
 * probes forever -- see the two commits before this one.  It now sends three
 * probes and two announcements and then goes quiet, which is what RFC 6762
 * asks for.
 *
 * It costs about 29 KiB of flash, and it turns LWIP_IGMP on for everyone,
 * since mdns.c requires IPv4 multicast.  Define LWIP_MDNS_RESPONDER to 0
 * before this header to decline both.
 */
#ifndef LWIP_MDNS_RESPONDER
#define LWIP_MDNS_RESPONDER 1
#endif

#if LWIP_MDNS_RESPONDER

/* mdns.c #errors without IPv4 multicast. */
#ifndef LWIP_IGMP
#define LWIP_IGMP 1
#endif

/* The responder keeps its per-netif state in a client-data slot. */
#ifndef LWIP_NUM_NETIF_CLIENT_DATA
#define LWIP_NUM_NETIF_CLIENT_DATA 1
#endif

/*
 * The responder needs eight timeouts of its own, not the one its header
 * comment suggests, and the difference is not academic: sys_timeout() drops
 * the request silently when the pool is full, so the shortfall showed up as
 * the second announcement never being sent.
 *
 * Where eight comes from.  mdns_resp_announce() calls
 * mdns_start_multicast_timeouts_ipv4() and _ipv6(), and each starts three --
 * the multicast timeout, the multicast probe timeout and the one at a quarter
 * of the TTL -- so six are live at once on a dual-stack build, and they are
 * started whether or not that family has an address.  Add one for the
 * probe-and-announce state machine itself, and one for
 * mdns_handle_tc_question(), which is transient but overlaps them.
 */
#ifndef MEMP_NUM_SYS_TIMEOUT
#define MEMP_NUM_SYS_TIMEOUT (LWIP_NUM_SYS_TIMEOUT_INTERNAL + 8)
#endif

#endif /* LWIP_MDNS_RESPONDER */

#endif /* __LWIPOPTS_H__ */
