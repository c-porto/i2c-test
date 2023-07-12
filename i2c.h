#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include "misc_def.h"

void i2c_setup(void) 

#define I2C_CONTROL_0       
#define I2C_CONTROL_1       
#define I2C_SW_RESET        
#define I2C_SLAVE_MODE      
#define I2C_SYNC_MODE       
#define I2C_EN_INTERRUPT    
#define I2C_OWN_ADDRESS     
#define SLAVE_ADDRESS_A     0x31
#define SLAVE_ADDRESS_B     0x32

#define SDA_REN     P3REN
#define SDA_OUT     P3OUT
#define SDA_SEL     P3SEL
#define SDA_PIN     BIT1

#define SCL_REN     P3REN
#define SCL_OUT     P3OUT
#define SCL_SEL     P3SEL
#define SCL_PIN     BIT2

#endif // !DEBUG
