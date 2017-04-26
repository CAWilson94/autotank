
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>

//hash defines


//GLOABLS
//voltaile int pirOn = 0;

int main( void )
{
  int pirOn = 0;
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
 // P1DIR |= (LED0 + LED1); // Set P1.0 to output direction 
  P1DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);//

  int i = 0;

  for(;;){
    i = (P1IN&BIT3);
    if(P1IN&8) {
      pirOn = 4;
    }
  }
}

