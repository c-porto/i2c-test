#ifndef TEST_H_
#define TEST_H_

// External includes
#include <msp430.h>
#include <stdint.h>
#include "misc_def.h"

//Conditional macros
#define DEBUG_MODE          0
#define MAX_CMD             10

// I2C definitions
#define I2C_FLAG            UCB1IFG
#define I2C_START_FLAG      UCSTTIFG
#define I2C_STOP_FLAG       UCSTPIFG
#define I2C_RX_FLAG         UCRXIFG0
#define I2C_TX_FLAG         UCTXIFG0
#define I2C_RX_BUFFER       UCB1RXBUF_L
#define I2C_TX_BUFFER       UCB1TXBUF_L

// UART definitions

//Variables
uint8_t command_bfr[MAX_CMD];                   // Store the commands received from I2C
uint8_t *ptr_command;                           // Receive the commands by the Rx Buffer of I2C.
uint8_t cmd_counter = 0;                            // Used to track number of commands

//task functions
void test_setup(void);
void test_run(void);
void ISR(void);

#endif // !TEST_H_
