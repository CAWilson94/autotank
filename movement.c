#include <msp430.h>
#include "movement.h"

/* CHANGE THESE FOR DIFFERENT PINS*/
#define MOTOR_LEFT_FORWARDS BIT0
#define MOTOR_RIGHT_FORWARDS BIT6 
#define MOTOR_LEFT_BACKWARDS BIT5
#define MOTOR_RIGHT_BACKWARDS BIT4 
#define BUTTON BIT5 //Only for testing

void movement_init(){
P1DIR |= (MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_FORWARDS + MOTOR_LEFT_BACKWARDS + MOTOR_RIGHT_BACKWARDS);
P1DIR &= ~BUTTON;
P1REN |= BUTTON;
P1OUT &= ~(MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_FORWARDS + MOTOR_LEFT_BACKWARDS + MOTOR_RIGHT_BACKWARDS);
P1IE |= BUTTON;
P1IFG &= ~BUTTON;
__enable_interrupt();
}

/*Movement C File*/
void move_body_forwards(){
//Motors hypothetically connected to pin 1.0 and 1.6
P1OUT |= (MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_FORWARDS);
P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_RIGHT_BACKWARDS);
}

/*H-Bridge Backwards OFF & FORWARDS ON*/
void move_body_backwards(){
P1OUT |= (MOTOR_LEFT_BACKWARDS + MOTOR_RIGHT_BACKWARDS);
P1OUT &= ~(MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_FORWARDS);
}

/*H-Bridge Backwards ON & FORWARDS OFF*/
void turn_body_right(int time_right){
  P1OUT |= (MOTOR_LEFT_FORWARDS);
  P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_RIGHT_FORWARDS + MOTOR_RIGHT_BACKWARDS);
  int i = 0;
  while (i< time_right){
    i++;
  }
  P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_BACKWARDS + MOTOR_RIGHT_FORWARDS);
}

void turn_body_left(int time_left){
  P1OUT |= (MOTOR_RIGHT_FORWARDS);
  P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_BACKWARDS);
  int i = 0; 
  while (i< time_left){
    i++;
  }
   P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_BACKWARDS + MOTOR_RIGHT_FORWARDS);
}

void rotate_180_right(){
  P1OUT |= (MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_BACKWARDS);
  P1OUT &= ~(MOTOR_LEFT_BACKWARDS + MOTOR_LEFT_FORWARDS);
}

void rotate_180_left(){
  P1OUT |= (MOTOR_RIGHT_FORWARDS + MOTOR_LEFT_BACKWARDS);
  P1OUT &= ~(MOTOR_RIGHT_BACKWARDS + MOTOR_LEFT_FORWARDS);
  
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  turn_body_left(32000);
  turn_body_right(32000);
  move_body_forwards();
  move_body_backwards();
//P1OUT ^= (MOTOR_LEFT_FORWARDS + MOTOR_RIGHT_FORWARDS); // P1.0 = toggle
P1IFG &= ~BUTTON; // P1.3 IFG cleared
}