
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; // don't touch it, it's for the watchdog stuff
  // CWILSON TEST
  return 0;
}
