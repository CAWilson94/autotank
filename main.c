#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "shooting.h"
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD; 
  /*
  P1DIR |= BIT2;
  P1SEL |= BIT2;
  
  TA0CCR0 = 26;
  TA0CCTL1 = OUTMOD_7;
  TA0CCR1 = 18;
  TA0CTL = TASSEL_2 + MC_1;*/
  shoot_5_sec_interval();
}
