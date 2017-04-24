#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>

#define LED_1 BIT0
#define INTERRUPT BIT2
#define LED_OUT P1OUT /* Port 1 output */
#define LED_DIR P1DIR /* Port 1 direction */ 

unsigned int timerCountB = 0;

// Configure timer
void ConfigTimerB(unsigned int delayCycles)
{
  TA0CCTL0 |= CCIE;	/* Interrupts on Timer:"capture/compare interrupt enable*/
  TA0CCR0 = delayCycles;/* Number of cycles in the timer counts to */
  TA0CTL |= TASSEL_1;	/* Timer0_A3 Control: Timer A clock source select: 1 - ACLK*/
  TA0CTL |= MC_1;	/* Timer0_A3 Control: 1 - Up to CCR0 mode */
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_B (void)
{
  
  P1OUT ^= LED_1;
  if(timerCountB >100)
  {
    timerCountB = 0;
  }
  
  timerCountB++;
}


int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  LED_DIR |= LED_1; /*Set P1.0 to output direction*/
  // LED_OUT &= ~LED_1; /* Set LED off */
  
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE = INTERRUPT; /* Set Port 1 interrupt enable reg */
  P1IFG &= ~INTERRUPT;
  
  ConfigTimerB(3000);
  __enable_interrupt();/* Loop and wait for interrupt */
  for(;;) {}
}
