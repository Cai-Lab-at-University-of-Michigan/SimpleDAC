#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pico/stdlib.h"

#include "simpledac.hpp"


// USB COM Libraries
#include <tusb.h>

#define INPUT_BUFFER_SIZE 32

int main()
{
    stdio_init_all();

    initialize_simpledac();

    char buffer[INPUT_BUFFER_SIZE];
    int index = 0;

    while (true)
    {
        int c = getchar_timeout_us(0); // non-blocking
        if (c == PICO_ERROR_TIMEOUT)
        {
            sleep_ms(10); // avoid tight loop
            continue;
        }

        if (c == '\n' || c == '\r')
        {
            buffer[index] = '\0';

            // Parse as integer
            int value = atoi(buffer);
            printf("Received number: %d\n", value);

            set_value_simpledac(0, value);
            set_value_simpledac(1, value);

            // Reset buffer
            index = 0;
            memset(buffer, 0, INPUT_BUFFER_SIZE);
        }
        else if (index < INPUT_BUFFER_SIZE - 1)
        {
            buffer[index++] = (char)c;
        }
    }

    return 0;
}