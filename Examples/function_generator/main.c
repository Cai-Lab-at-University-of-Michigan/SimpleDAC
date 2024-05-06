#include "../../simpledac.c"

#include <stdio.h>
#include "pico/stdlib.h"

void main() {
    initialize_simpledac();

    uint16_t v = 0;

    while(1) {
        set_value_simpledac(0, v);
        set_value_simpledac(1, v);
        v++;
    }
}