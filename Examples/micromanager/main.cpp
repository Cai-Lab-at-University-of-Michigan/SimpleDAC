#include <stdio.h>
#include "pico/stdlib.h"

#include "simpledac.hpp"

unsigned int version = 2;

const size_t output_pin_count = 4;
const int output_pins[output_pin_count] = {22, 26, 27, 28};
char current_output_pattern = 0;

void write_outputs()
{
    for (int i = 0; i < output_pin_count; i++)
    {
        const uint8_t id = output_pins[i];
        const bool val = ((current_output_pattern >> i) & 1) != 0;
        gpio_put(id, val);
    }
}

int main()
{
    stdio_init_all();

    initialize_simpledac();
    set_value_simpledac(0, 32768);
    set_value_simpledac(1, 32768);

    for (size_t i = 0; i < output_pin_count; i++)
    {
        // Initialize Input Pin
        gpio_init(output_pins[i]);
        gpio_set_dir(output_pins[i], GPIO_OUT);
        gpio_put(output_pins[i], 0);
    }

    int channel;
    char msb, lsb;
    uint16_t towrite;

    // Loop forever
    while (1)
    {
        int in_int = PICO_ERROR_TIMEOUT;

        do
        {
            in_int = getchar_timeout_us(10000); // 10ms
        } while (in_int == PICO_ERROR_TIMEOUT);

        char in_byte = (char)in_int;

        switch (in_byte)
        {
        case 0:
            break;

        case 1:
            current_output_pattern = getchar();
            write_outputs();
            printf("%c", (char)in_byte);
            break;

        case 2:
            printf("%c", (char)in_byte);
            printf("%c", (char)current_output_pattern);
            break;

        case 3:
            channel = getchar();
            msb = getchar();
            lsb = getchar();

            towrite = ((uint16_t)(((uint8_t)msb) << 8)) | (uint8_t)lsb;
            towrite <<= (16 - 12); // Micromanager puts out 12 bit numbers

            set_value_simpledac((int)channel, towrite);

            printf("%c", (char)in_byte);
            printf("%c", (char)channel);
            printf("%c", msb);
            printf("%c", lsb);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
        case 30:
            printf("MM-Ard\n");
            break;
        case 31:
            printf("%d\n", version);
            break;
        case 40:
            printf("%d", 40);
            printf(0);
            break;
        case 41:
            break;
        case 42:
            break;
        }
    }

    return 0;
}