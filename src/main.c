#include "device.h"

#include "LK.h"

void debug(uint32_t out) {
    GPIO_PMOD_DIR = 0xF;
    GPIO_PMOD_OUT = 0;
    GPIO_PMOD_OUT = out;
    GPIO_PMOD_OUT = 0;
}

uint64_t get_cycles(void) {
    uint32_t high;
    uint32_t high2;
    uint32_t low;
    do {
        asm volatile ("rdcycleh %0" : "=r" (high));
        asm volatile ("rdcycle %0"  : "=r" (low));
        asm volatile ("rdcycleh %0" : "=r" (high2));
    } while (high != high2);
    return ((uint64_t) high << 32) | low;
}

uint32_t get_timestamp_ms(void) {
    // Note: assumes (16 * 1024 * 1024) Hz clock.
    // Actually gives in units of 1.024ms.
    return (uint32_t)(get_cycles() >> 14);
}

void recv_data(uint8_t* data, uint32_t count) {
    while (count > 0) {
        uint32_t avail = HOST_RX_COUNT;
        uint32_t transfer = count > avail ? avail : count;
        count -= transfer;

        uint8_t* end = data + transfer;
        while (data < end) {
            *data = HOST_RX_DATA;
            data++;
        }
    }
}

void send_byte(uint8_t data) {
    while (HOST_TX_COUNT >= HOST_TX_MAX)
        ;
    HOST_TX_DATA = data;
}

void send_data(uint8_t* data, uint32_t count) {
    while (count > 0) {
        uint32_t avail = HOST_TX_MAX - HOST_TX_COUNT;
        uint32_t transfer = count > avail ? avail : count;
        count -= transfer;

        uint8_t* end = data + transfer;
        while (data < end) {
            HOST_TX_DATA = *data;
            data++;
        }
    }
}

uint8_t recv_byte() {
    while (HOST_RX_COUNT == 0)
        ;
    return HOST_RX_DATA;
}


int main() {
    while (1) {
        if (HOST_RX_COUNT > 0) {
            // A command byte is ready.
            uint8_t command = HOST_RX_DATA;
            lk_loop(command);
            continue;
        }

        // Periodic updates
        lk_runtime = get_timestamp_ms();
        lk_cart_power_off_proc();
    }
    return 0;
}
