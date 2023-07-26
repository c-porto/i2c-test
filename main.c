#include <msp430.h>

#include "i2c.h"
#include "test.h"

void main(void){
    WDTCTL = WDTPW + WDTHOLD;
    i2c_setup();
    test_run();
}
