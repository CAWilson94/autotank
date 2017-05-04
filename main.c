
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
  //  ir_init();
  ping();
  __enable_interrupt();
  for(;;){
    if (get_move_value() == 0){
     P2OUT |= (BIT3);
     P1OUT &= ~BIT7;
    P2OUT |= (BIT4);
   P2OUT &= ~(BIT5);
   __delay_cycles(1000000);          // delay for 30ms (after this time echo times out if there is no object detected)
    
  P2OUT |= (BIT3 + BIT4 + BIT5);
     P1OUT |= BIT7;
    }//   ir_run();    
  run_ping();
       // __delay_cycles(1000000);          // delay for 30ms (after this time echo times out if there is no object detected)

    
  }
}
