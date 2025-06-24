cmake_minimum_required(VERSION 3.13)

#set(PICO_BOARD pico)
#set(PICO_BOARD pico_w)
set(PICO_BOARD pico2)

# If pico2 is selected you have to select PICO_PLATFORM
set(PICO_PLATFORM rp2350-arm-s)
#set(PICO_PLATFORM rp2350-riscv)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_COLOR_DIAGNOSTICS ON)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(firmware C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

#pico_generate_pio_header(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/spi_tx.pio)


pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib hardware_spi)
