
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ping.h"
#include "ir_sense.h"

/*
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
 // movement_init();
 // counter_attack();
  P1DIR |= BIT0;
  P1OUT |= BIT0;*/
  void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	/*P1DIR |= (BIT0 + BIT1 + BIT2 + BIT3);
	P1OUT |= (BIT0 + BIT3);
	P1OUT &= ~(BIT1 + BIT2);*/
        ir_init();
       __enable_interrupt();
        for(;;){
        ir_run();
        }
}
