import serial
import time

a = serial.Serial('/dev/tty.usbmodem112401', baudrate=115200)

while True:
    for v in [b'\x01\x00', b'\01\x3f']:
        a.write(v)
        print(a.read(1))
        time.sleep(2)