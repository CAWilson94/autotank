#include <msp430.h>
#include <stdio.h>

#define LED0 BIT0
#define LED1 BIT6
#define BUTTON BIT3

/////GLOBAL VARIABLES HERE////////////
int counter = 0;

/* Shoot every 5 seconds repeatadly
Can only shoot for 0.2 seconds at a time
@C.A.Wilson

Interrupt 
Timer
*/

void shoot_5_sec_interval()
{}

void config_pins(){
  P1DIR |= LED0;   // set P1DIR with P0 to high (1)
  P1DIR &= ~BUTTON; //set P1.3 (Switch 2) as input
  P1OUT &= ~LED0; //turn led off
  P1REN |= BUTTON; 
  P1OUT &= BUTTON;
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE = BUTTON;   /* Set Port 1 interrupt enable reg */
  P1IFG &= ~BUTTON; //clear interrupt 
}


#pragma vector=PORT1_VECTOR
__interrupt void sw_int(void)
{
  P1OUT ^= LED0;
  P1IFG &= ~BUTTON;
}

