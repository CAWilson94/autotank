#include <msp430.h>
#include <stdio.h>

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
  P1DIR |= BIT0;   // set P1DIR with P0 to high (1)
  P1DIR &= ~BIT3; //set P1.3 (Switch 2) as input
  P1OUT &= ~BIT0; //turn led on
  P1REN |= BIT3; 
  P1OUT &= BIT3;
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE = BIT3;   /* Set Port 1 interrupt enable reg */
  //P1IFG &= ~BIT3; //clear interrupt 
}



#pragma vector=PORT1_VECTOR
__interrupt void sw_int(void)
{
  P1OUT |= BIT0;
}


void counter_attack()
{
  
}