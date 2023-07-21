#include "test.h"
#include <stdint.h>

void ISR(void) {

    // Start
    if (I2C_FLAG & I2C_START_FLAG) {
        ptr_command  = (uint8_t *)command_bfr;
        BIT_CLEAR(I2C_FLAG, I2C_START_FLAG);
    }

    // RX
    if (I2C_FLAG & I2C_RX_FLAG) {
        *ptr_command++ = I2C_RX_BUFFER;         //Receive the commands from master.
        cmd_counter++;
    }


    // Stop
    if(I2C_FLAG & I2C_STOP_FLAG) {
        BIT_CLEAR(I2C_FLAG, I2C_STOP_FLAG);
    }
}

void test_setup(void){
    #if defined(DEBUG_MODE) && (DEBUG_MODE == 0)
         #define UART_MODE
        // configure UART
    #endif    
}

void test_run(void){
    // Run just the debug
    while (1) {
        #if defined (UART_MODE)
            //UART stuff
        #endif 
        ISR();
        if (cmd_counter >= MAX_CMD) {                   // Needed to avoid going out of buffer length
            ptr_command = (uint8_t *) command_bfr;      // or &command_bfr[0];
        }
        //delay maybe?
    }
}
