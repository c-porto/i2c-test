from pyftdi import i2c
from time import sleep

commands: list[bytes] = [
    b"\xAA",
    b"\xAD",
    b"\xA1",
    b"\xA2",
    b"\xA3",
    b"\xA4",
    b"\xA5",
    b"\xBA",
    b"\xBB",
    b"\xBC",
    b"\xBD",
    b"\xA9",
    b"\xC0",
    b"\xB0",
    b"\xB1",
    b"\xB2",
    b"\xB3",
    b"\xB4",
    b"\xB5",
    b"\xB6",
    b"\xB7",
    b"\xC3",
]

ctrl = i2c.I2cController()
# Mudar para o valor real
ctrl.configure("ftdi:232h")

port = ctrl.get_port(0x31)

for cmd in commands:
    print(f"Data transmitted from master via i2c: {cmd}")
    rx: bytes = port.exchange(cmd, 1)
    print(f"Data received from slave via i2c: {rx}")
    sleep(1)
