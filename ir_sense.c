#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ir_sense.h" 

int noAction=0;
int timercount =0;
int fired =0;
int moveturret =0;

void ir_init(){
    BCSCTL1 = CALBC1_8MHZ;                     //Set DCO to 8Mhz
    DCOCTL = CALDCO_8MHZ;
    P2DIR &= ~(BIT1 + BIT2);  
    P1DIR |= BIT0 + BIT1 + BIT2; 
    P1OUT &= ~(BIT0 + BIT1 + BIT2);
  
    TA0CCR0 = 32000;/* Number of cycles in the timer counts to */
    TA0CTL |= TASSEL_1;	/* Timer0_A3 Control: Timer A clock source select: 1 - ACLK*/
    TA0CTL |= MC_1;	/* Timer0_A3 Control: 1 - Up to CCR0 mode */
    TA0CCTL0 |= CCIE;
    
  }
  
void ir_run(){
  
  if(((!(P2IN&2) == 0)&& (!(P2IN&4) == 0)) && fired ==0) {
     P1OUT &= ~(BIT0 + BIT1 + BIT2 +BIT3 + BIT4);
  }
  else if((P2IN&2 ) ==0 && fired == 0){
    moveturret = 1;
    TA0CCTL0 |= CCIE;	
    fired = 1;
    
  }
  else if(((P2IN&4) ==0 ) && fired == 0){
    moveturret = 2;
    TA0CCTL0 |= CCIE;	
    fired = 1;
  }
}

int getNoAction() {
  return noAction;
}

void setNoAction(int i) {
  noAction = i;
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
   if (moveturret==1){
  P1OUT |= BIT1;
  P1OUT &= ~BIT2;
  }
  else if(moveturret ==2){
  P1OUT |= BIT2;
  P1OUT &= ~BIT1;
  }
  
  timercount++;
  if(timercount>5)
  {
    TA0CCTL0 &= ~CCIE;
    P1OUT &= ~(BIT0 + BIT1 + BIT2);
    timercount = 0;
    fired = 0;
  }  
}