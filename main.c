
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
  P1DIR |= (BIT0+BIT6);   // set P1DIR with P0 and P6 to high (1)
  P1OUT &= ~BIT6;
  P1OUT |= BIT0; 
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE = BIT2;   /* Set Port 1 interrupt enable reg */
  P1IFG &= ~BIT2; //clear interrupt
  config_timer_A();  
  __enable_interrupt();
  for(;;){
    
  }
}
