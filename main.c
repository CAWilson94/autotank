#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "shooting.h"
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  counter_attack();
  shoot_5_sec_interval();
  
    for(;;) {}
}
