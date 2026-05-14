#include "device.h"

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

int main() {
    char str[] = "hello, world!";
    send_data((uint8_t*) str, sizeof(str));
    return 0;
}
