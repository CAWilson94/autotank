#include <msp430.h>
#include "movement.h"

#define MOTORLEFT BIT0
#define MOTORRIGHT BIT6 
#define BUTTON BIT3

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^= (MOTORLEFT + MOTORRIGHT); // P1.0 = toggle
P1IFG &= ~BUTTON; // P1.3 IFG cleared
//P1IES ^= BIT3; // toggle the interrupt edge,
// the interrupt vector will be called
// when P1.3 goes from HitoLow as well as
// LowtoHigh
}

void configure_pins(){
P1DIR |= (MOTORLEFT + MOTORRIGHT);
P1DIR &= ~BUTTON;
P1REN |= BUTTON;
P1OUT &= ~(MOTORLEFT + MOTORRIGHT);
P1IE |= BUTTON;
P1IFG &= ~BUTTON;
}

/*Movement C File*/
void move_body_forward(){
//Motors hypothetically connected to pin 1.0 and 1.6

  
}

void move_body_backwards(){}

void turn_body_right(double degrees_right){}

void turn_body_left(double degrees_left){}

void rotate_180_right(){}

void rotate_180_left(){}