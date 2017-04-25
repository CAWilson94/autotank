#include <msp430.h>
#include <stdio.h>
#include <intrinsics.h>

/* Shoot every 5 seconds repeatadly
Can only shoot for 0.2 seconds at a time
@C.A.Wilson: disclaimer, idiot on the loose

Interrupt 
Timer
*/

#define LED_1 BIT0
#define INTERRUPT BIT2
#define LED_OUT P1OUT /* Port 1 output */
#define LED_DIR P1DIR /* Port 1 direction */ 


unsigned int flag = 0;
unsigned int timerCount = 0;

unsigned int waiting_to_shoot = 0;
unsigned int shooting_time = 0;

// Configure timer
void ConfigTimerA(unsigned int delayCycles)
{
  /* Using ACLK  32kHz crystal clock */
  TA0CCTL0 |= CCIE;	/* Interrupts on Timer:"capture/compare interrupt enable*/
  TA0CCR0 = delayCycles;/* Number of cycles in the timer counts to */
  TA0CTL |= TASSEL_1;	/* Timer0_A3 Control: Timer A clock source select: 1 - ACLK*/
  TA0CTL |= MC_1;	/* Timer0_A3 Control: 1 - Up to CCR0 mode */
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  timerCount++;
  if(timerCount >5)
  {
    flag =1;
    timerCount=0;
  }
}

// Shoot every five seconds
void shoot_5_sec_interval()
{
  LED_DIR |= LED_1; /*Set P1.0 to output direction*/
  // LED_OUT &= ~LED_1; /* Set LED off */
  
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE =INTERRUPT; /* Set Port 1 interrupt enable reg */
  P1IFG &= ~INTERRUPT;
  
  ConfigTimerA(32000);
  __enable_interrupt();/* Loop and wait for interrupt */
  while(1)
  {
    if (flag==1)
    {
      P1OUT ^= LED_1;
     __delay_cycles(6400);/* Stops the code & waits for 6400 cycles to pass*/
     P1OUT ^= LED_1;
      flag =0;
    }
    
  }
  
  
}


void counter_attack()
{
}