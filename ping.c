#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "movement.h"
/*int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  movement_init();
  for(;;){
  move_body_forwards();
  }*/

#define trigger BIT2
#define echo BIT3

#define trigger_two BIT4
#define echo_two BIT5

#define trigger_three BIT6
#define echo_three BIT7

int miliseconds;
int distance;
long sensor;

void main(void)
{
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;                     // submainclock 1mhz
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 1000;				    // 1ms at 1mhz
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  P1IFG  = 0x00;			    //clear all interrupt flags
  P1DIR |= BIT0;     //0x01;                // P1.0 as output for LED
  P1OUT &= ~BIT0;    //0x01;                // turn LED off
  
  _BIS_SR(GIE);                 	    // global interrupt enable
 
 while(1){
	/*PING1*/
        P1IE &= ~BIT0; //0x01;			// disable interupt
	P1DIR |= trigger + trigger_two + trigger_three; //0x02;			// trigger pin as output
	P1OUT |= trigger + trigger_two + trigger_three; //0x02;			// generate pulse
	__delay_cycles(10);             // for 10us
	P1OUT &= ~(trigger+trigger_two + trigger_three);      //0x02;                 // stop pulse
  	P1DIR &= ~(echo + echo_two + echo_three);      //0x04;			// make pin P1.2 input (ECHO)
        P1IFG = 0x00;                   // clear flag just in case anything happened before
	P1IE |= (echo + echo_two + echo_three);        //0x04;			// enable interupt on ECHO pin
	P1IES &= ~(echo + echo_two + echo_three);      //0x04;			// rising edge on ECHO pin
        __delay_cycles(30000);          // delay for 30ms (after this time echo times out if there is no object detected)
        distance = sensor/58;           // converting ECHO lenght into cm
        if(distance < 20 && distance != 0) P1OUT |= BIT0;//0x01;  //turning LED on if distance is less than 20cm and if distance isn't 0.
        else P1OUT &= ~BIT0;//0x01;
        
 }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	if(P1IFG&echo)  //is there interrupt pending?
        {
          if(!(P1IES&echo)) // is this the rising edge?
          {			
            TACTL|=TACLR;   // clears timer A
            miliseconds = 0;
            P1IES |= echo;  //falling edge
             P1IES &= ~echo_two;  //falling edge
              P1IES &= ~echo_three;  //falling edge
          }
          else
          {
            sensor = (long)miliseconds*1000 + (long)TAR;	//calculating ECHO lenght

          }
          
	P1IFG &= ~echo;				//clear flag
        P1IFG &= ~echo_two;	
        P1IFG &= ~echo_three;
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  miliseconds++;
}

	

