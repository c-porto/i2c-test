#ifndef TEST_H_
#define TEST_H_

// External includes
#include <msp430.h>
#include <stdint.h>
#include "misc_def.h"

// I2C definitions
#define I2C_FLAG            UCB1IFG
#define I2C_START_FLAG      UCSTTIFG
#define I2C_STOP_FLAG       UCSTPIFG
#define I2C_RX_FLAG         UCRXIFG0
#define I2C_TX_FLAG         UCTXIFG0
#define I2C_RX_BUFFER       UCB1RXBUF_L
#define I2C_TX_BUFFER       UCB1TXBUF_L

//LED definitions
#define LED

//task functions
void test_setup(void);
void test_run(void);

#endif // !TEST_H_
