
#include <stdio.h>
#include <intrinsics.h>
#include <msp430.h>
#include "ping.h"
#include "ir_sense.h"

  void main()
{
	
  WDTCTL = WDTPW + WDTHOLD;
  ir_init();
  init_ping();
  P2DIR |= (BIT4 + BIT5 );
  __enable_interrupt();
   __delay_cycles(5000000);    
  for(;;){
    
    if ((get_move_value() == 0)){
      run_ping();
      if(getNoAction()==10) {
        setMoveVal(1);
      }
    } 
    ir_run();    
   run_ping();
    }
   
  
}
