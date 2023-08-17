#ifndef I2C_H_
#define I2C_H_

#include "misc_def.h"
#include <msp430.h>

void i2c_setup(void);

#define I2C_CONTROL_0 UCB1CTLW0
#define I2C_SW_RESET UCSWRST
#define I2C_SLAVE_MODE UCMODE_3
#define I2C_SYNC_MODE UCSYNC
#define I2C_EN_INTERRUPT UCB1IE
#define ADDRESS0_ENABLE UCOAEN
#define I2C_OWN_ADDRESS UCB1I2COA0
#define SLAVE_ADDRESS_A 0x31
#define SLAVE_ADDRESS_B 0x32

#define SDA_REN P3REN
#define SDA_OUT P3OUT
#define SDA_SEL0 P3SEL0
#define SDA_SEL1 P3SEL1
#define SDA_PIN BIT1

#define SCL_REN P3REN
#define SCL_OUT P3OUT
#define SCL_SEL0 P3SEL0
#define SCL_SEL1 P3SEL1
#define SCL_PIN BIT2

#define INIT_PIN LOCKLPM5
#define P_INIT_REG PM5CTL0

#endif // !DEBUG
