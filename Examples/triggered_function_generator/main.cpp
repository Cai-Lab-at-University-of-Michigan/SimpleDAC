#include <stdio.h>
#include "pico/stdlib.h"

#include "simpledac.hpp"

#include <cmath> // Required for pow()

#define INPUT_PIN 28

int main() {
    stdio_init_all();

    initialize_simpledac();
    set_value_simpledac(0, 0);
    set_value_simpledac(1, 0);

    // Initialize Input Pin
    gpio_init(INPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);
    gpio_pull_up(INPUT_PIN); // Optional: Pull-up resistor if button goes to GND

    // Loop forever
    while(1) {
        // Wait for trigger
        while(!gpio_get(INPUT_PIN));

        for(size_t i = 0; i < 128 * 2 * 2; i++){
            uint16_t v = 128 * i;

            // Write value and increment
            set_value_simpledac(0, v);
            set_value_simpledac(1, v);

            sleep_us(125);
        }

        set_value_simpledac(0, 0);
        set_value_simpledac(1, 0);

        // Wait for trigger to return
        while(gpio_get(INPUT_PIN));
    }
    
    return 0;
}