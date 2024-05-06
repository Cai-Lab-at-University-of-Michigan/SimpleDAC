// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// RPI-specific libraries
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

// SPI Frequency definitions
#define SPI_FREQ 40
#define MHz (1000 * 1000)
#define OUTPUT_BUFFER_SIZE 3

// SPI Bus A settings
#define cs_pinA 5
#define sck_pinA 6
#define mosi_pinA 7
#define miso_pinA 8

// SPI Bus B settings
#define cs_pinB 9
#define sck_pinB 10
#define mosi_pinB 11
#define miso_pinB 12

// Define spi bus #'s
spi_inst_t *spiA = spi0; // SPI Bus 0
spi_inst_t *spiB = spi1; // SPI Bus 1

// Define buffers for SPI output
void *data_outA;
void *data_outB;

void initialize_simpledac()
{
    // Create output buffers
    data_outA = malloc(OUTPUT_BUFFER_SIZE);
    data_outB = malloc(OUTPUT_BUFFER_SIZE);
    memset(data_outA, 0, OUTPUT_BUFFER_SIZE);
    memset(data_outB, 0, OUTPUT_BUFFER_SIZE);

    // Set CS pins as output
    gpio_init(cs_pinA);
    gpio_set_dir(cs_pinA, GPIO_OUT);
    gpio_put(cs_pinA, 1);
    gpio_init(cs_pinB);
    gpio_set_dir(cs_pinB, GPIO_OUT);
    gpio_put(cs_pinB, 1);

    // Turn on the two SPI busses
    spi_init(spiA, SPI_FREQ * MHz); // 1MHz
    // BUS -- BITS -- POLARITY -- PHASE -- ENDIAN
    spi_set_format(spiA, 8, 0, 1, SPI_LSB_FIRST);
    spi_init(spiB, SPI_FREQ * MHz); // 1MHz
    // BUS -- BITS -- POLARITY -- PHASE -- ENDIAN
    spi_set_format(spiB, 8, 0, 1, SPI_LSB_FIRST);

    // Assign all GPIO pins for SPI
    gpio_set_function(sck_pinA, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pinA, GPIO_FUNC_SPI);
    gpio_set_function(miso_pinA, GPIO_FUNC_SPI);
    gpio_set_function(sck_pinB, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pinB, GPIO_FUNC_SPI);
    gpio_set_function(miso_pinB, GPIO_FUNC_SPI);
}

void set_value_simpledac(int channel, unsigned short new_value)
{
    if (channel < 0 || channel > 1)
    {
        return;
    }

    // Find the right SPI channel
    spi_inst_t *spi = spiA;
    if (channel == 1)
    {
        spi = spiB;
    }

    // Find the right CS pin
    uint8_t cs_pin = cs_pinA;
    if (channel == 1)
    {
        cs_pin = cs_pinB;
    }

    void *data_out_ptr = data_outA;
    if (channel == 1)
    {
        data_out_ptr = data_outB;
    }

    // Casts the 2nd and 3rd byte of the buffer to a uint16_t and inverts the val
    *(uint16_t *)(data_out_ptr + 1) = (new_value >> 8) | (new_value << 8);

    // Write the data with CS->LOW
    gpio_put(cs_pin, 0);
    spi_write_blocking(spi, data_out_ptr, OUTPUT_BUFFER_SIZE);
    gpio_put(cs_pin, 1);
}