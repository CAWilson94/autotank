
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "movement.h"
#include "ir_sense.h"
#include "shooting.h"
#include "turret_movement.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
 // movement_init();
 // counter_attack();
  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  for(;;){}
}
