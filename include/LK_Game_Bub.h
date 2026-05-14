#ifndef _LK_GAME_BUB_H_
#define _LK_GAME_BUB_H_

#include "device.h"

#define HARDWARE_GAMEBUB

#define LK_DEVICE_NAME 				"Game Bub"
#define LK_PCB_VERSION				1
#define LK_POWER_CONTROL_SUPPORT	true
#define LK_BOOTLOADER_RESET_SUPPORT	false

void debug_out(uint32_t id);

#define dprint(s, params...) {}

uint32_t get_timestamp_ms();
void recv_data(uint8_t* data, uint32_t count);
void send_byte(uint8_t data);
void send_data(uint8_t* data, uint32_t count);

#define __NOP() asm volatile("nop")


// Delays including overhead, measured with Saleae w/ PicoRV32 @ 16MHz
#define _delay_100ns()		{} // 300ns
#define _delay_200ns()		{} // 300ns
#define _delay_300ns()		{} // 300ns
#define _delay_400ns()		{ __NOP(); } // 480ns
#define _delay_500ns()		{ __NOP(); } // 480ns
#define _delay_us(us)		{ for (u32 delay = 0; delay < us; delay++) { __NOP(); __NOP(); __NOP(); } } // 20.6 us at (20)
#define _delay_ms(ms)		_delay_us(ms * 1000) // 2.02ms at (2)
#define _delay_dmg_slow_access()	_delay_us(2)

#define _timeout_init()		{ time_start = TIMESTAMP_NOW(); }
#define _timeout_reset()	{ time_start = 0; }
#define _timeout_check()	((time_start > 0) && (TIMESTAMP_NOW() - time_start > 500))

#define PIN_WR				(1 << 26)
#define PIN_RD				(1 << 25)
#define PIN_CS				(1 << 24)
#define PIN_CS2				(1 << 28)
#define PIN_AUDIO			(1 << 29)
#define PIN_CLK				(1 << 27)
#define VOLTAGE_SELECT		(1 << 31) // No pin
#define PIN_WR_H()			GPIO_CART_OUT_SET = (PIN_WR)
#define PIN_WR_L()			GPIO_CART_OUT_CLR = (PIN_WR)
#define PIN_RD_H()			GPIO_CART_OUT_SET = (PIN_RD)
#define PIN_RD_L()			GPIO_CART_OUT_CLR = (PIN_RD)
#define PIN_CS_H()			GPIO_CART_OUT_SET = (PIN_CS)
#define PIN_CS_L()			GPIO_CART_OUT_CLR = (PIN_CS)
#define PIN_CS2_H()			GPIO_CART_OUT_SET = (PIN_CS2)
#define PIN_CS2_L()			GPIO_CART_OUT_CLR = (PIN_CS2)
#define PIN_AUDIO_H()		GPIO_CART_OUT_SET = (PIN_AUDIO)
#define PIN_AUDIO_L()		GPIO_CART_OUT_CLR = (PIN_AUDIO)
#define PIN_CLK_H()			GPIO_CART_OUT_SET = (PIN_CLK)
#define PIN_CLK_L()			GPIO_CART_OUT_CLR = (PIN_CLK)
// #define PIN_CLK_H()			GPIO_PMOD_OUT = (1)
// #define PIN_CLK_L()			GPIO_PMOD_OUT = (0)
#define PIN_ADDR_H(pin)		GPIO_CART_OUT_SET = (1 << (pin))
#define PIN_ADDR_L(pin)		GPIO_CART_OUT_CLR = (1 << (pin))

#define CART_POWER_ON()				{ GPIO_CART_EN = 1; }
#define CART_POWER_OFF()			{ GPIO_CART_EN = 0; }
#define ACTIVITY_LED_ON()			{ /* no led */ }
#define ACTIVITY_LED_OFF()			{ /* no led */ }
#define SET_VOLTAGE_3_3V()			{ /* no voltage control */ }
#define SET_VOLTAGE_5V()			{ /* no voltage control */ }
#define AUTO_POWEROFF_RESUME()		auto_off_timer_suspended = false
#define AUTO_POWEROFF_SUSPEND()		auto_off_timer_suspended = true
#define TIMESTAMP_NOW()				get_timestamp_ms()

#define RAW_PINS_DIR_OUT()	{ GPIO_CART_DIR = 0xFF; }
#define RAW_PINS_DIR_IN()	{ GPIO_CART_DIR = 0x00; }

#define PIN_AUDIO_DIR_OUT()	{ GPIO_CART_DIR_SET = (1 << 5); }
#define PIN_AUDIO_DIR_IN()	{ GPIO_CART_DIR_CLR = (1 << 5); }

#define PULLUPS_ON()		{ /* pullups not configurable */ }
#define PULLUPS_OFF()		{ /* pullups not configurable */ }

#define CONN_RECV(data, count)	recv_data(data, count)
#define CONN_SEND_BYTE(data)	send_byte(data)
#define CONN_SEND(data, count)	send_data(data, count)
#define BOOTLOADER_RESET()		{ /* no bootloader */ }

#define DISABLE_INTERRUPTS()	{ /* no interrupts */ }
#define ENABLE_INTERRUPTS()		{ /* no interrupts */ }

#define CHUNK_MAX_LEN 64

// GB/GBC
#define RAW_DMG_ADDR_SET(addr)	{ GPIO_CART_OUT = (GPIO_CART_OUT & 0xFFFF0000) | (addr); }
#define RAW_DMG_DATA_SET(data)	{ GPIO_CART_OUT = (GPIO_CART_OUT & 0xFF00FFFF) | ((data) << 16); }

#define RAW_DMG_ADDR_DIR_OUT()	{ GPIO_CART_DIR_SET = 0b011; }
#define RAW_DMG_ADDR_DIR_IN()	{ GPIO_CART_DIR_CLR = 0b011; }
#define RAW_DMG_DATA_DIR_OUT()	{ GPIO_CART_DIR_SET = 0b100; }
#define RAW_DMG_DATA_DIR_IN()	{ GPIO_CART_DIR_CLR = 0b100; }

#define RAW_DMG_DATA_GET()		((GPIO_CART_IN >> 16) & 0xFF)

// GBA
#define RAW_AGB_ADDR_SET(addr)	{ GPIO_CART_OUT = (GPIO_CART_OUT & 0xFF000000) | (addr); }
#define RAW_AGB_DATA_SET(data)	{ GPIO_CART_OUT = (GPIO_CART_OUT & 0xFFFF0000) | (data); }

#define RAW_AGB_ADDR_DIR_OUT()	{ GPIO_CART_DIR_SET = 0b111; }
#define RAW_AGB_ADDR_DIR_IN()	{ GPIO_CART_DIR_CLR = 0b111; }
#define RAW_AGB_DATA_DIR_OUT()	{ GPIO_CART_DIR_SET = 0b011; }
#define RAW_AGB_DATA_DIR_IN()	{ GPIO_CART_DIR_CLR = 0b011; }

#define RAW_AGB_DATA_GET()		(GPIO_CART_IN & 0xFFFF)

// GBA EEPROM
#define PIN_A0_H()			PIN_ADDR_H(0)
#define PIN_A0_L()			PIN_ADDR_L(0)
#define PIN_A0_OUT()		{ RAW_AGB_ADDR_DIR_OUT() }
#define PIN_A0_IN()			{ RAW_AGB_ADDR_DIR_IN() }

#endif