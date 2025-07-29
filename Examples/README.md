# Code Examples

| Demo Name         | Folder Path                          | Description                          |
|-------------------|-------------------------------------|--------------------------------------|
| micromanager      | Examples/micromanager                | Enables control of  |
| Triggered Function Generator | Examples/triggered_function_generator          | Generates different waveforms, with or without triggering |
| Serial Function Generator  | Examples/serial_function_generator        | Allows user input to control DAC through a serial connection   |

## Building Code Examples

A file, `build.sh` is included with each code example which uses [https://github.com/lukstep/raspberry-pi-pico-docker-sdk](lukstep/raspberry-pi-pico-docker-sdk) to build the example code inside of Docker:
`# sh build.sh`

Alternatively, these source files can be built using the Raspberry Pi Pico SDK, installed manually.