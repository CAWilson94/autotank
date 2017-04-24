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
{
  printf("YER MAW");
}

/* Timer A0 interrupt service routine*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
  P1OUT ^= BIT0;//&= ~BIT0;//
    if (counter >100){
    counter = 0;}
    counter++;
} 

void config_timer_A(){
      
   
   TA0CCTL0 = CCIE; //enable interrupts for CCRO 
   TA0CCR0 = 16000; //6000; //set timer A0 counter target
   TA0CTL |= TASSEL_1;	//Use ACLK as source for timer
   TA0CTL |= MC_1;	//Use UP mode timer
}
void counter_attack()
{
  
}