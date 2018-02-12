#include "mbed.h"
#include <stdint.h>
#include "loragw_hal.h"


// main() runs in its own thread in the OS
int main() {
    printf("started");
    uint8_t i = lgw_start();
    if (i == LGW_HAL_SUCCESS) {
        printf("INFO: concentrator started, packet can now be received\n");
    } else {
        printf("ERROR: failed to start the concentrator\n");
        return EXIT_FAILURE;
    }
}
