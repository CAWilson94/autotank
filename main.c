
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  return 0;
}

void move_body_forward(){}

void move_body_backwards(){}

void turn_body_right(){}

void turn_body_left(){}

void rotate_body_right(){}

void rotate_body_left(){}