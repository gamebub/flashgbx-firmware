#pragma once

#include <stdint.h>

#define MMIO_BASE          0x02000000

#define HOST_TX_MAX        4096
#define HOST_TX_COUNT      *(volatile uint32_t*)(MMIO_BASE + 0x0100)
#define HOST_TX_DATA       *(volatile  uint8_t*)(MMIO_BASE + 0x0104)
#define HOST_RX_MAX        4096
#define HOST_RX_COUNT      *(volatile uint32_t*)(MMIO_BASE + 0x0110)
#define HOST_RX_DATA       *(volatile  uint8_t*)(MMIO_BASE + 0x0114)

#define GPIO_PMOD_DIR      *(volatile uint32_t*)(MMIO_BASE + 0x0200)
#define GPIO_PMOD_OUT      *(volatile uint32_t*)(MMIO_BASE + 0x0204)
#define GPIO_PMOD_IN       *(volatile uint32_t*)(MMIO_BASE + 0x0208)

#define GPIO_CART_DIR      *(volatile uint32_t*)(MMIO_BASE + 0x0300)
#define GPIO_CART_DIR_SET  *(volatile uint32_t*)(MMIO_BASE + 0x0304)
#define GPIO_CART_DIR_CLR  *(volatile uint32_t*)(MMIO_BASE + 0x0308)
#define GPIO_CART_OUT      *(volatile uint32_t*)(MMIO_BASE + 0x0310)
#define GPIO_CART_OUT_SET  *(volatile uint32_t*)(MMIO_BASE + 0x0314)
#define GPIO_CART_OUT_CLR  *(volatile uint32_t*)(MMIO_BASE + 0x0318)
#define GPIO_CART_IN       *(volatile uint32_t*)(MMIO_BASE + 0x0320)
#define GPIO_CART_EN       *(volatile uint32_t*)(MMIO_BASE + 0x0380)

#define GPIO_LINK_DIR      *(volatile uint32_t*)(MMIO_BASE + 0x0400)
#define GPIO_LINK_OUT      *(volatile uint32_t*)(MMIO_BASE + 0x0410)
#define GPIO_LINK_IN       *(volatile uint32_t*)(MMIO_BASE + 0x0420)
