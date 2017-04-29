
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
#define LED_2 BIT6
#define INTERRUPT BIT2
#define LED_OUT P1OUT /* Port 1 output */
#define LED_DIR P1DIR /* Port 1 direction */ 
#define LED_SEL P1SEL /* Port 1 select*/ 
#define BUTTON BIT3
#define A0 11
#define A1 21
#define PAUSE 92
#define B0 24
#define B1 8 

unsigned int flag = 0;
unsigned int shooting = 0;
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

void ConfigTimerB()
{
  /* Using SCLK  1MHZ crystal clock */
  TA1CCR0 = 26;                          // 1000us
  TA1CCTL0 = OUTMOD_7;                      // CCR1 reset/set
  TA1CCR1 = 18;                            // CCR1 PWM duty cycle
  TA1CCTL1 = OUTMOD_7;                      // CCR2 reset/set
  TA1CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
}

           // A1,  X, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0, A1, A0 

int shot[] = {A1,PAUSE,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,
              B1,B0,B1,B0,B1,B0,
              A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,
              A1,PAUSE,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,A1,A0,
              B1,B0,B1,B0,B1,B0,
              A1,A0,B1,B0,A1,A0,B1,B0,A1,A0,B1,B0,A1,A0};
  
int i = 0;
int j = 0;

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1 (void)
{
  
  
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{  
  
  if(timerCount >= 5)
  {
    
    unsigned int length = sizeof(shot) / sizeof(int*);
    if(j < length){            // j is in the middle of shooting
     // case_duty_cycle();     // Duty cycle toggling for each part of signal
      ConfigTimerA(shot[j]);   // Call ISR in shot[j] cycles
      j++;                     // increment j for next time ISR is called
      //P1OUT ^= LED_1;        // toggle LED
      
      if(flag == 1)
      {                         // Whether the PWM should be on or off, 1 = on
        P1SEL &= ~LED_1;       // Turn off PWM output
        flag = 0;              // Turn off next time ISR is called
      }
      else {                   // 0 = off
        P1SEL |= LED_1;        // Start PWM output
        flag = 1;              // Start PWM timer next time ISR is called
      }
    } else {                   // j finished shooting
      j = 0;                   // reset j for next time ISR is called
      timerCount = 0;          // reset count to 0, so ISR is called 5 times
      ConfigTimerA(32000);  // call ISR in 32000 cycles, i.e. 1 second
  } 
  } else {
    timerCount++;              // not been 5 seconds yet, add to count.
  }
}

// Shoot every five seconds
void shoot_5_sec_interval()
{
  LED_DIR |= LED_1; /*Set P1.0 to output direction*/
  LED_OUT &= ~LED_1; /* Set LED off */
  LED_DIR |= LED_2; /*Set P1.0 to output direction*/
  LED_OUT &= ~LED_2; /* Set LED off */
  
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE =( INTERRUPT + BUTTON); /* Set Port 1 interrupt enable reg */
  P1IFG &= ~(INTERRUPT + BUTTON);
  
  ConfigTimerA(32000);
  ConfigTimerB();
  __enable_interrupt();/* Loop and wait for interrupt */
  while(1)
  {
    if (flag==1)
    {
      //P1OUT ^= LED_1;
      //__delay_cycles(6400);/* Stops the code & waits for 6400 cycles to pass*/
      //P1OUT ^= LED_1;
      shooting = 1;
      //TA0CCR0 = 10;  
    } 
  } 
}


void counter_attack()
{
  P1DIR |= BIT0;   // set P1DIR with P0 to high (1)
  P1DIR &= ~BUTTON; //set P1.3 (Switch 2) as input
  P1OUT &= ~BIT0; //turn led off
  P1REN |= BUTTON; 
  P1OUT &= BUTTON;
  P1IES = 0; /* Set INT1 interrupt edge select reg */
  P1IE |= BUTTON;   /* Set Port 1 interrupt enable reg */
  P1IFG &= ~BUTTON; //clear interrupt
  __enable_interrupt();
}
#pragma vector=PORT1_VECTOR
__interrupt void sw_int(void)
{
  P1OUT ^= BIT0;
  P1IFG &= ~BUTTON;
}
