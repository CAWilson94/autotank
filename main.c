
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "shooting.h"
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  // Testing 
  // shoot_5_sec_interval();
  config_pins();
//  config_timer_A();
  __enable_interrupt();
  for(;;){   
  }
}
