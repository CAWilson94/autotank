#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>

int main( void )
{
  WDTCTL = WDTPW | WDTHOLD; 

}

