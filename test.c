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
uint8_t *ptr_cmd_buffer =
    (uint8_t *)command_bfr; // Used for store last commands
uint8_t *ptr_rsp_buffer =
    (uint8_t *)responde_bfr; // Used for store last commands
uint8_t cmd_counter = 0;     // Used to track number of commands
uint8_t rsp_counter = 0;     // Used to track number of responses
uint8_t state;               // Used for generating different responses
uint8_t sq_counter = 0;      // used for sequencial simulation
// Store the amount of time that the burn-wire system was active.
uint32_t deploy_timer_1, deploy_timer_2, deploy_timer_3, deploy_timer_4;
// Store the amount of times the deployment system was active.
uint8_t deploy_counter_1, deploy_counter_2, deploy_counter_3, deploy_counter_4;

#if defined(ECHO) && (ECHO == 1)
void command_read(void) {
  switch (command[0]) {
  case ARM:
    response[0] = RES_ARM;
    response[1] = RES_ARM;
    break;
  case RESET:
    response[0] = RES_RESET;
    response[1] = RES_RESET;
    break;
  case DISARM:
    response[0] = RES_DISARM;
    response[1] = RES_DISARM;
    break;
  case DEPLOY_ANT_1:
    response[0] = RES_DEPLOY_ANT_1;
    response[1] = RES_DEPLOY_ANT_1;
    break;
  case DEPLOY_ANT_2:
    response[0] = RES_DEPLOY_ANT_2;
    response[1] = RES_DEPLOY_ANT_2;
    break;
  case DEPLOY_ANT_3:
    response[0] = RES_DEPLOY_ANT_3;
    response[1] = RES_DEPLOY_ANT_3;
    break;
  case DEPLOY_ANT_4:
    response[0] = RES_DEPLOY_ANT_4;
    response[1] = RES_DEPLOY_ANT_4;
    break;
  case DEPLOY_SEQUENCIAL:
    response[0] = RES_DEPLOY_SEQUENCIAL;
    response[1] = RES_DEPLOY_SEQUENCIAL;
    break;
  case DEPLOY_ANT_1_OVERRIDE:
    response[0] = RES_DEPLOY_ANT_1_OVERRIDE;
    response[1] = RES_DEPLOY_ANT_1_OVERRIDE;
    break;
  case DEPLOY_ANT_2_OVERRIDE:
    response[0] = RES_DEPLOY_ANT_2_OVERRIDE;
    response[1] = RES_DEPLOY_ANT_2_OVERRIDE;
    break;
  case DEPLOY_ANT_3_OVERRIDE:
    response[0] = RES_DEPLOY_ANT_3_OVERRIDE;
    response[1] = RES_DEPLOY_ANT_3_OVERRIDE;
    break;
  case DEPLOY_ANT_4_OVERRIDE:
    response[0] = RES_DEPLOY_ANT_4_OVERRIDE;
    response[1] = RES_DEPLOY_ANT_4_OVERRIDE;
    break;
  case DEPLOY_CANCEL:
    response[0] = RES_DEPLOY_CANCEL;
    response[1] = RES_DEPLOY_CANCEL;
    break;
  case MEASURE_TEMPERATURE:
    response[0] = RES_MEASURE_TEMPERATURE;
    response[1] = RES_MEASURE_TEMPERATURE;
    break;
  case REPORT_DEPLOY_TIMER_1:
    response[0] = RES_REPORT_DEPLOY_TIMER_1;
    response[1] = RES_REPORT_DEPLOY_TIMER_1;
    break;
  case REPORT_DEPLOY_TIMER_2:
    response[0] = RES_REPORT_DEPLOY_TIMER_2;
    response[1] = RES_REPORT_DEPLOY_TIMER_2;
    break;
  case REPORT_DEPLOY_TIMER_3:
    response[0] = RES_REPORT_DEPLOY_TIMER_3;
    response[1] = RES_REPORT_DEPLOY_TIMER_3;
    break;
  case REPORT_DEPLOY_TIMER_4:
    response[0] = RES_REPORT_DEPLOY_TIMER_4;
    response[1] = RES_REPORT_DEPLOY_TIMER_4;
    break;
  case REPORT_DEPLOY_COUNTER_1:
    response[0] = RES_REPORT_DEPLOY_COUNTER_1;
    response[1] = RES_REPORT_DEPLOY_COUNTER_1;
    break;
  case REPORT_DEPLOY_COUNTER_2:
    response[0] = RES_REPORT_DEPLOY_COUNTER_2;
    response[1] = RES_REPORT_DEPLOY_COUNTER_2;
    break;
  case REPORT_DEPLOY_COUNTER_3:
    response[0] = RES_REPORT_DEPLOY_COUNTER_3;
    response[1] = RES_REPORT_DEPLOY_COUNTER_3;
    break;
  case REPORT_DEPLOY_COUNTER_4:
    response[0] = RES_REPORT_DEPLOY_COUNTER_4;
    response[1] = RES_REPORT_DEPLOY_COUNTER_4;
    break;
  case REPORT_DEPLOY_STATUS:
    response[0] = RES_REPORT_DEPLOY_STATUS;
    response[1] = RES_REPORT_DEPLOY_STATUS;
    break;
  default:
    response[0] = 0x88;
    response[1] = 0x88;
  }
}
#endif /* ECHO MODE */
void sequencial(void) {
  switch (sq_counter) {
  case 0:
    deploy_counter_1++;
    break;
  case 1:
    deploy_counter_2++;
    break;
  case 2:
    deploy_counter_3++;
    break;
  case 3:
    deploy_counter_4++;
    break;
  default:
    sq_counter = 0;
    break;
  }
}
#if defined(ECHO) && (ECHO == 0)
void command_read(void) {
  switch (command[0]) {
  case ARM:
    // do nothing
    break;
  case RESET:
    // do nothing
    break;
  case DISARM:
    // do nothing
    break;
  case DEPLOY_ANT_1:
    deploy_counter_1++;
    deploy_timer_1++;
    break;
  case DEPLOY_ANT_2:
    deploy_counter_2++;
    deploy_timer_2++;
    break;
  case DEPLOY_ANT_3:
    deploy_counter_3++;
    deploy_timer_3++;
    break;
  case DEPLOY_ANT_4:
    deploy_counter_4++;
    deploy_timer_4++;
    break;
  case DEPLOY_SEQUENCIAL:
    sequencial();
    break;
  case DEPLOY_ANT_1_OVERRIDE:
    deploy_counter_1++;
    deploy_timer_1++;
    break;
  case DEPLOY_ANT_2_OVERRIDE:
    deploy_counter_2++;
    deploy_timer_2++;
    break;
  case DEPLOY_ANT_3_OVERRIDE:
    deploy_counter_3++;
    deploy_timer_3++;
    break;
  case DEPLOY_ANT_4_OVERRIDE:
    deploy_counter_4++;
    deploy_timer_4++;
    break;
  case DEPLOY_CANCEL:
    break;
  case MEASURE_TEMPERATURE:
    response[0] = 0xFF;
    response[1] = 0x03;
    break;
  case REPORT_DEPLOY_TIMER_1:
    deploy_timer_1 = deploy_timer_1;
    response[0] = (deploy_timer_1 & 0xFF00) >> 8;
    response[1] = (deploy_timer_1 & 0xFF);
    break;
  case REPORT_DEPLOY_TIMER_2:
    deploy_timer_2 = deploy_timer_2;
    response[0] = (deploy_timer_2 & 0xFF00) >> 8;
    response[1] = (deploy_timer_2 & 0xFF);
    break;
  case REPORT_DEPLOY_TIMER_3:
    deploy_timer_3 = deploy_timer_3;
    response[0] = (deploy_timer_3 & 0xFF00) >> 8;
    response[1] = (deploy_timer_3 & 0xFF);
    break;
  case REPORT_DEPLOY_TIMER_4:
    deploy_timer_4 = deploy_timer_4;
    response[0] = (deploy_timer_4 & 0xFF00) >> 8;
    response[1] = (deploy_timer_4 & 0xFF);
    break;
  case REPORT_DEPLOY_COUNTER_1:
    response[0] = deploy_counter_1;
    response[1] = 0x00;
    break;
  case REPORT_DEPLOY_COUNTER_2:
    response[0] = deploy_counter_2;
    response[1] = 0x00;
    break;
  case REPORT_DEPLOY_COUNTER_3:
    response[0] = deploy_counter_3;
    response[1] = 0x00;
    break;
  case REPORT_DEPLOY_COUNTER_4:
    response[0] = deploy_counter_4;
    response[1] = 0x00;
    break;
  case REPORT_DEPLOY_STATUS:
    response[0] = 0xFF;
    response[1] = 0xFF;
    break;
  default:
    response[0] = 0x88;
    response[1] = 0x88;
  }
}
#endif /* SIMULATED BEHAVIOR MODE */

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
  command_read();
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
  }
}
