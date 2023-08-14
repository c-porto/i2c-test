from pyftdi import i2c
from time import sleep

commands: list[bytes] = [
    b"\xAA",
    b"\xAC",
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
# Should not respond = S'R
responses: list[str] = [
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "S'R | 0x88 0x88",
    "Should return 11 bits of temperature | 0x03 0xFF",
    "Should return deploy_counter_1 | 0x02 0x02",
    "Should return deploy_counter_2 | 0x02 0x02",
    "Should return deploy_counter_3 | 0x02 0x02",
    "Should return deploy_counter_4 | 0x02 0x02",
    "Should return deploy_timer_1 | 0x02 0x02",
    "Should return deploy_timer_2 | 0x02 0x02",
    "Should return deploy_timer_3 | 0x02 0x02",
    "Should return deploy_timer_4 | 0x02 0x02",
    "Should return deploy_status | 0xFF 0xFF",
]

ctrl = i2c.I2cController()
# Mudar para o valor real
ctrl.configure("ftdi:232h")

port = ctrl.get_port(0x31)

for idx,cmd in enumerate(commands):
    print(f"Data transmitted from master via i2c: {cmd}")
    rx = port.exchange(cmd,2)
    print(f"{responses[idx]}, actual response is {rx}")
    sleep(1)
