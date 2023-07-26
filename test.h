#ifndef TEST_H_
#define TEST_H_

// External includes
#include "misc_def.h"
#include <msp430.h>
#include <stdint.h>

// General Macros
#define PERIOD 157 // Direct conversion to msp430f5529 to msp430fr6989
#define MAX_CMD 10

// I2C definitions
#define I2C_FLAG UCB1IFG
#define I2C_START_FLAG UCSTTIFG
#define I2C_STOP_FLAG UCSTPIFG
#define I2C_RX_FLAG UCRXIFG0
#define I2C_TX_FLAG UCTXIFG0
#define I2C_RX_BUFFER UCB1RXBUF_L
#define I2C_TX_BUFFER UCB1TXBUF_L

// Response types for debugging
#define RESPONSE_1 1
#define RESPONSE_2 2
#define RESPONSE_3 3
#define DEFAULT_RESPONSE 4

// task functions
void change_state(void);
void generate_response(void);
void ISR(void);
void test_run(void);

#endif // !TEST_H_
