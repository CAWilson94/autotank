#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ir_sense.h" 

int main(void)

{
  WDTCTL = WDTPW + WDTHOLD;   //Stop WDT
  ir_init();
  ir_run();
  while(1){
  }
}

 

 
