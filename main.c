
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "movement.h"
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  return 0;
}

