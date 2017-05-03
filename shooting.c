#include <msp430.h>
#include <stdio.h>
#include <intrinsics.h>

/* Shoot every 5 seconds repeatadly
Can only shoot for 0.2 seconds at a time
@C.A.Wilson: disclaimer, idiot on the loose

Interrupt 
Timer
*/

#define INTERRUPT BIT2
#define LED_OUT P1OUT /* Port 1 output */
#define LED_DIR P1DIR /* Port 1 direction */ 
#define LED_SEL P1SEL /* Port 1 select*/ 
#define A0 11
#define A1 21
#define PAUSE 92
#define B0 24
#define B1 8 

int j = 0;
int i = 0;
unsigned int flag = 0;
unsigned int shooting = 0;
unsigned int timerCount = 0;

           // A1,  X, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0 
int shot[] = {A1,PAUSE,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,
              B1,B0,B1,B0,B1,B0,
              A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,
              A1,PAUSE,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,
              B1,B0,B1,B0,B1,B0,
              A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,B1,B0,A1,A0};
 
void ConfigTimerA(unsigned int delayCycles)
{
  /* Using ACLK  32kHz crystal clock */
  TA0CCTL0 |= CCIE;	/* Interrupts on Timer:"capture/compare interrupt enable*/
  TA0CCR0 = delayCycles;/* Number of cycles in the timer counts to */
  TA0CTL |= TASSEL_1;	/* Timer0_A3 Control: Timer A clock source select: 1 - ACLK*/
  TA0CTL |= MC_1;	/* Timer0_A3 Control: 1 - Up to CCR0 mode */
}

void ConfigTimerB()
{
  /* Using SCLK  1MHZ crystal clock */
  TA1CCR0 = 26;         /* 26us*/
  TA1CCTL0 = OUTMOD_7;  /* CCR0 reset/set */
  TA1CCR1 = 13;         /* CCR0 PWM duty cycle */
  TA1CCTL1 = OUTMOD_7;  /* CCR0 reset/set */
  TA1CTL = TASSEL_2 + MC_1 + TACLR;     /* SMCLK, up mode, clear TAR */
}


void pwm_output()
{
  if(timerCount >= 5)
  {
    if(i<4){
      
      unsigned int length = sizeof(shot) / sizeof(int*);
      if(j < length){            /* j is in the middle of shooting*/
        ConfigTimerA(shot[j]);   /*Call ISR in shot[j] cycles*/
        j++;                     /* increment j for next time ISR is called*/
        if(flag == 1)
        {                        /* Whether the PWM should be on or off, 1 = on*/
          P2SEL &= ~BIT2;       /* Turn off PWM output*/
          flag = 0;              /* Turn off next time ISR is called*/
        }
        else {                   /* 0 = off*/
          P2SEL |= BIT2;        /*Start PWM output*/
          flag = 1;              /*Start PWM timer next time ISR is called*/
        }
      } else {                   /* j finished shooting*/
        j = 0;                   /* reset j for next time ISR is called*/
         i++;
      } 
      
    }
    else
    {
      i=0;
      timerCount = 0;          /* reset count to 0, so ISR is called 5 times*/
      ConfigTimerA(32000);  /* call ISR in 32000 cycles, i.e. 1 second*/
    }
  }
  
  else {
    timerCount++;              /* not been 5 seconds yet, add to count*/
  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  pwm_output();

}

// Shoot every five seconds
void shoot_5_sec_interval()
{
  P2DIR |= BIT2; /*p2.2 for PWM output*/
  P2SEL &= ~BIT2;
  P2OUT &= ~BIT2;
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE =( INTERRUPT + BIT3); /* Set Port 1 interrupt enable reg */
  P1IFG &= ~(INTERRUPT + BIT3);
  
  ConfigTimerA(32000);
  ConfigTimerB();
  __enable_interrupt();/* Loop and wait for interrupt */
  while(1)
  {
    if (flag==1)
    {
      shooting = 1; 
    } 
  } 
}


void counter_attack()
{
  P1DIR |= BIT0;   // set P1DIR with P0 to high (1)
  P1DIR &= ~BIT3; //set P1.3 (Switch 2) as input
  P1OUT &= ~BIT0; //turn led off
  P1REN |= BIT3; 
  P1OUT &= BIT3;
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE |= BIT3;   /* Set Port 1 interrupt enable reg */
  P1IFG &= ~BIT3; //clear interrupt
  __enable_interrupt();
}
#pragma vector=PORT1_VECTOR
__interrupt void sw_int(void)
{
  P1OUT ^= BIT0;
  P1IFG &= ~BIT3;
}
