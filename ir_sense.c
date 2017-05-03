#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ir_sense.h" 

void ir_init(){
    WDTCTL = WDTPW + WDTHOLD;            //Stop WDT
    BCSCTL1 = CALBC1_8MHZ;                     //Set DCO to 8Mhz
    DCOCTL = CALDCO_8MHZ;
    P2DIR &= ~BIT0;   // IR SENSOR IS CONNECTED TO PORT2 OF BIT0
    P1DIR |= BIT0 + BIT5;
    P1OUT &= ~(BIT0 + BIT5);
  }
  
void ir_run(){
 // __delay_cycles(1000000);
  
  if(P2IN == 0x01) //  IF IR IS HIGH
  {  
     P1OUT &= ~(BIT0 + BIT5);
  __delay_cycles(1000000);//GIVE SOME DELAY
  }
  else
  {
   
    P1OUT |= BIT0 + BIT5;
  __delay_cycles(1000000); // GIVE SOME DELAY
  }
  
}