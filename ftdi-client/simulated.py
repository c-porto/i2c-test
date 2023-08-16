from pyftdi import i2c
from time import sleep

# Commands without parameters and response
initial_commands = [
    b"\xAA",  # RESET
    b"\xAC",  # DISARM
    b"\xAD",  # ARM ANTENNA SYSTEM
    b"\xA9",  # CANCEL DEPLOY SYSTEM ACTIVATION
]

# Commands with parameters but with no response
deploy_commands = [
    b"\xA1",  # DEPLOY ANTENNA 1
    b"\xA2",  # DEPLOY ANTENNA 2
    b"\xA3",  # DEPLOY ANTENNA 3
    b"\xA4",  # DEPLOY ANTENNA 4
    b"\xA5",  # DEPLOY SEQUENCIAL
    b"\xBA",  # DEPLOY ANTENNA 1 OVERRIDE
    b"\xBB",  # DEPLOY ANTENNA 2 OVERRIDE
    b"\xBC",  # DEPLOY ANTENNA 3 OVERRIDE
    b"\xBD",  # DEPLOY ANTENNA 4 OVERRIDE
]

# Commands with 2 byte responses and no parameters
report_2b_commands = [
    b"\xB4",  # REPORT DEPLOY TIME 1
    b"\xB5",  # REPORT DEPLOY TIME 2
    b"\xB6",  # REPORT DEPLOY TIME 3
    b"\xB7",  # REPORT DEPLOY TIME 4
    b"\xC3",  # REPORT DEPLOYMENT STATUS
    b"\xC0",  # MEASURE TEMPERATURE
]

# Commands with 1 byte responses and no parameters
report_1b_commands = [
    b"\xB0",  # REPORT DEPLOY COUNTER 1
    b"\xB1",  # REPORT DEPLOY COUNTER 2
    b"\xB2",  # REPORT DEPLOY COUNTER 3
    b"\xB3",  # REPORT DEPLOY COUNTER 4
]

# Responses for report_2b_commands
responses_2b: list[str] = [
    "Should return deploy_timer_1 | 0x02 0x00",
    "Should return deploy_timer_2 | 0x02 0x00",
    "Should return deploy_timer_3 | 0x02 0x00",
    "Should return deploy_timer_4 | 0x02 0x00",
    "Should return deploy_status | 0xFF 0xFF",
    "Should return 11 bits of temperature | 0x03 0xFF",
]

# Responses for report_1b_commands
responses_1b: list[str] = [
    "Should return deploy_counter_1 | 0x02",
    "Should return deploy_counter_2 | 0x02",
    "Should return deploy_counter_3 | 0x02",
    "Should return deploy_counter_4 | 0x02",
]

ctrl = i2c.I2cController()

# Mudar para o valor real
ctrl.configure("ftdi:232h")

port = ctrl.get_port(0x31)

# TESTING COMMANDS WITHOUT PARAMETERS/RESPONSE
for cmd in initial_commands:
    print(f"Data transmitted from master via i2c: {cmd}")
    port.write(cmd)
    sleep(10)

# TESTING COMMANDS WITHOUT RESPONSE, BUT WITH PARAMETERS
for cmd in deploy_commands:
    print(f"Data transmitted from master via i2c: {cmd}")
    port.write(cmd, relax=False)
    port.write(cmd)
    sleep(10)

# TESTING COMMANDS WITHOUT PARAMETERS, BUT WITH 1 BYTE RESPONSE
for idx, cmd in enumerate(report_1b_commands):
    rx = port.exchange(cmd)
    print(f"{responses_1b[idx]}, actual response is {rx}")
    sleep(10)

# TESTING COMMANDS WITHOUT PARAMETERS, BUT WITH 2 BYTE RESPONSE
for idx, cmd in enumerate(report_2b_commands):
    port.write(cmd)
    rx = port.read(2)
    print(f"{responses_2b[idx]}, actual response is {rx}")
    sleep(10)
