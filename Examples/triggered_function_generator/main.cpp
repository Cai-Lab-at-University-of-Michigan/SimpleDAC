#include <stdio.h>
#include "pico/stdlib.h"

#include "simpledac.hpp"

#include <cmath> // Required for pow()

#define INPUT_PIN 28

#define TRIGGER 0 // Trigger mode
#define FUNCT 5   // Function to output (see below)

/*
    1 => Constant value
*/

#define PERIOD 10000 // us

int main()
{
    stdio_init_all();

    initialize_simpledac();

    // Initialize Input Pin
    gpio_init(INPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);

    // Loop forever
    while (1)
    {
        // Wait for trigger
        if (TRIGGER)
        {
            while (!gpio_get(INPUT_PIN))
                ;
        }

        uint64_t start = time_us_64();
        while (time_us_64() < start + PERIOD)
        {
            uint16_t v = 0;
            float phase = time_us_64() - start;
            phase /= PERIOD; // 0...1 phase

            switch (FUNCT)
            {
            case 1: // Constant Value
                v = 32768;
                break;
            case 2: // Sawtooth
                phase *= 65535;
                v = phase;
                break;
            case 3: // Square
                if (phase < 0.5)
                {
                    v = 65535;
                }
                else
                {
                    v = 0;
                }
                break;
            case 4: // Sine wave
                phase = (sin(phase * 3.14159 * 2) + 1.0) / 2.0;
                phase *= 65535;
                v = phase;
                break;
            case 5: // Triangle
                if (phase > 0.5)
                {
                    phase -= 0.5;
                    phase /= 0.5;
                } else {
                    phase /= 0.5;
                    phase = 1.0 - phase;
                }
                phase *= 65535;
                v = phase;
                break;
            }

            set_value_simpledac(0, v);
            set_value_simpledac(1, v);
        }

        // Wait for trigger to return to neutral
        if (TRIGGER)
        {
            while (gpio_get(INPUT_PIN))
                ;
        }
    }

    return 0;
}