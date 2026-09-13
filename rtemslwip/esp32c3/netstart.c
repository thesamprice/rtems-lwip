/*
 * start_networking() for riscv/esp32c3db.
 *
 * Copyright (C) 2026 Samuel Price <thesamprice@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials publish with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES ARE DISCLAIMED.
 */

/*
 * Unlike every other BSP with a port here, the ESP32-C3 has no Ethernet
 * controller.  Its only network interface is the WiFi radio, and that is
 * driven by Espressif's binary libraries, which are not part of rtems-lwip and
 * should not become part of it -- they are 8 closed archives and a 120-entry
 * OS shim.
 *
 * So this file starts the stack and stops.  Adding the interface is left to a
 * weak hook that the WiFi driver overrides, which keeps the dependency
 * pointing the right way: rtems-lwip knows nothing about the WiFi port, and
 * the WiFi port knows about lwIP.
 *
 * An application that links no driver still gets a working stack -- loopback,
 * the socket API, the tcpip thread -- and a message saying why it has no
 * interface, rather than a link error naming a symbol it has never heard of.
 */

#include <netstart.h>

#include <lwip/netif.h>
#include <lwip/tcpip.h>

#include <rtems/bspIo.h>

/*
 * Overridden by the WiFi driver.  Returns 0 on success.
 *
 * Weak rather than a registration call because it has to run after
 * start_networking_shared() and before start_networking() returns, and a
 * registration API would mean either an ordering rule for the application to
 * get wrong or a second entry point for it to forget.
 */
int __attribute__((weak)) esp32c3_netif_add(
  struct netif  *net_interface,
  ip_addr_t     *ipaddr,
  ip_addr_t     *netmask,
  ip_addr_t     *gateway,
  unsigned char *mac_address
)
{
  (void) net_interface;
  (void) ipaddr;
  (void) netmask;
  (void) gateway;
  (void) mac_address;

  printk(
    "esp32c3: the stack is up but there is no interface.  This part has no\n"
    "esp32c3: Ethernet controller; link a WiFi driver providing\n"
    "esp32c3: esp32c3_netif_add() to get one.\n"
  );

  return 1;
}

int start_networking(
  struct netif  *net_interface,
  ip_addr_t     *ipaddr,
  ip_addr_t     *netmask,
  ip_addr_t     *gateway,
  unsigned char *mac_ethernet_address
)
{
  if ( start_networking_shared() != RTEMS_SUCCESSFUL ) {
    return 1;
  }

  return esp32c3_netif_add(
    net_interface,
    ipaddr,
    netmask,
    gateway,
    mac_ethernet_address
  );
}
