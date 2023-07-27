#include "test.h"
#include <stdint.h>

// Variables
uint8_t *ptr_command;  // Receive the commands by the Rx Buffer of I2C.
uint8_t *ptr_response; // Pointer for I2C purposes (initializate the response[]
                       // in the first position).
uint8_t response[2];   // The response that will be send when requested from a
                       // command.
uint8_t command[2];    // store temporary commands
uint8_t command_bfr[MAX_CMD];  // Store the commands received from I2C
uint8_t responde_bfr[MAX_CMD]; // Store the responses transmitted to I2C
uint8_t *ptr_cmd_buffer = (uint8_t *)command_bfr; // Used for store last commands
uint8_t *ptr_rsp_buffer = (uint8_t *)responde_bfr; // Used for store last commands
uint8_t cmd_counter = 0;     // Used to track number of commands
uint8_t rsp_counter = 0;     // Used to track number of responses
uint32_t timer = 0;          // Keep track of time
uint8_t state;               // Used for generating different responses

void change_state(void) {
  if ((timer % 2) == 0) {
    state = RESPONSE_1;
  } else if ((timer % 3) == 0) {
    state = RESPONSE_2;
  } else if ((timer % 5) == 0) {
    state = RESPONSE_3;
  } else {
    state = DEFAULT_RESPONSE;
  }
}
void generate_response(void) {
  switch (state) {
  case RESPONSE_1:
    response[1] = 0x11;
    response[0] = 0x11;
    break;
  case RESPONSE_2:
    response[1] = 0x22;
    response[0] = 0x22;
    break;
  case RESPONSE_3:
    response[1] = 0x33;
    response[0] = 0x33;
    break;
  default:
    response[1] = 0x77;
    response[0] = 0x77;
    break;
  }
}
void ISR(void) {
  // Start
  if (I2C_FLAG & I2C_START_FLAG) {
    ptr_command = (uint8_t *)command;
    ptr_response = (uint8_t *)response;
    BIT_CLEAR(I2C_FLAG, I2C_START_FLAG);
  }
  // RX
  if (I2C_FLAG & I2C_RX_FLAG) {
    *ptr_cmd_buffer = I2C_RX_BUFFER;
    *ptr_command++ = *ptr_cmd_buffer++;
    cmd_counter++;
  }
  // TX
  if (I2C_FLAG & I2C_TX_FLAG) {
    *ptr_rsp_buffer = *ptr_response++;
    I2C_TX_BUFFER = *ptr_rsp_buffer++;
    rsp_counter++;
  }
  // Stop
  if (I2C_FLAG & I2C_STOP_FLAG) {
    BIT_CLEAR(I2C_FLAG, I2C_STOP_FLAG);
    response[0] = 0x88;
    response[1] = 0x88;
  }
  change_state();
  generate_response();
}

void test_run(void) {
  while (1) {
    if (cmd_counter >= MAX_CMD) { // Needed to avoid going out of buffer length
      ptr_cmd_buffer = (uint8_t *)command_bfr; // or &command_bfr[0];
      cmd_counter = 0;
    }
    if (rsp_counter >= MAX_CMD) { // Needed to avoid going out of buffer length
      ptr_rsp_buffer = (uint8_t *)responde_bfr; // or &command_bfr[0];
      cmd_counter = 0;
    }
    ISR();
    __delay_cycles(PERIOD);
    ++timer;
  }
}
