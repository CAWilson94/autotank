#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ir_sense.h" 

int timercount =0;
int fired =0;
int moveturret =0;

void ir_init(){
    WDTCTL = WDTPW + WDTHOLD;            //Stop WDT
    BCSCTL1 = CALBC1_8MHZ;                     //Set DCO to 8Mhz
    DCOCTL = CALDCO_8MHZ;
    P2DIR &= ~(BIT1 + BIT2 +BIT3 + BIT4);   // IR SENSOR IS CONNECTED TO PORT2 OF BIT0
    P1DIR |= BIT0 + BIT1 + BIT2 +BIT3 + BIT4; 
    P1OUT &= ~(BIT0 + BIT1 + BIT2 +BIT3 + BIT4);
  
    TA0CCR0 = 32000;/* Number of cycles in the timer counts to */
    TA0CTL |= TASSEL_1;	/* Timer0_A3 Control: Timer A clock source select: 1 - ACLK*/
    TA0CTL |= MC_1;	/* Timer0_A3 Control: 1 - Up to CCR0 mode */
    
  }
  
void ir_run(){
 // __delay_cycles(1000000);
  
 /* if(P2IN == 0x02 && fired ==0) //  IF IR IS HIGH
  {  
     P1OUT &= ~(BIT0 + BIT5);
//  __delay_cycles(1000000);//GIVE SOME DELAY
  }
  else*/ 
  /*if(fired == 0){
    P1OUT |= BIT0 + BIT5;
    TA0CCTL0 |= CCIE;	
    fired = 1;
  */
  
  if(((!(P2IN&2) == 0)&& (!(P2IN&4) == 0)) && fired ==0) {
     P1OUT &= ~(BIT0 + BIT1 + BIT2 +BIT3 + BIT4);
  }
  else if((P2IN&2 ) ==0 && fired == 0){
  //  P1OUT |= BIT0 + BIT1;
    moveturret = 1;
    TA0CCTL0 |= CCIE;	
    fired = 1;
    
  }
  else if(((P2IN&4) ==0 ) && fired == 0){
  //  P1OUT |= BIT0 + BIT2;
    moveturret = 2;
    TA0CCTL0 |= CCIE;	
    fired = 1;
  }
  
  /*
  else if(!(P2IN&BIT3 ==1 ) && fired == 0){
  P1OUT |= BIT0 + BIT3;
    TA0CCTL0 |= CCIE; 
    fired = 1;
  }
  else if(!(P2IN&BIT4 ==1 ) && fired == 0){
  P1OUT |= BIT0 + BIT4;
    TA0CCTL0 |= CCIE;	
    fired = 1;
  }
  */
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
 // pwm_output();
  
  if (moveturret==1){
  P1OUT |= BIT1;
  P1OUT &= ~BIT2;
  }
  else if(moveturret ==2){
  P1OUT |= BIT2;
  P1OUT &= ~BIT1;
  }
  
  timercount++;
  if(timercount>4)
  {
    TA0CCTL0 &= ~CCIE;
    P1OUT &= ~(BIT0 + BIT1 + BIT2 +BIT3 + BIT4);
    timercount = 0;
    fired = 0;
  }
}