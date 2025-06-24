#include <stdio.h>
#include "pico/stdlib.h"

#include "simpledac.hpp"

int main() {
    stdio_init_all();

    initialize_simpledac();

    // Counter
    uint16_t v = 32768; // 0;

    // Loop forever
    while(1) {
        // Write value and increment
        set_value_simpledac(0, v);
        set_value_simpledac(1, v);
        //v += 1024;

        sleep_ms(1);
    }
    
    return 0;
}