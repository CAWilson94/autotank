#include <msp430g2553.h>

int miliseconds;
int distance;
long sensor;
int move = 0;
int turn = 0;
int time_motor = 0;

void init_ping()
{
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;                     // submainclock 1mhz
  
  TA1CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA1CCR0 = 1000;				    // 1ms at 1mhz
  TA1CTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  P1IFG  = BIT0;			    //clear all interrupt flags
  P1DIR |= BIT0 + BIT5;                            // P1.0 as output for LED
  P1DIR &= BIT6;
  P1OUT &= ~BIT0;                           // turn LED off
}

 void run_ping(){
	P1IE &= ~BIT6;			// disable interupt
	P1DIR |= BIT5; 			// trigger pin as output
	P1OUT |= BIT5;			// generate pulse
	__delay_cycles(10);             // for 10us
	P1OUT &= ~BIT5;                 // stop pulse
  	P1DIR &= ~BIT6;			// make pin P1.6 input (ECHO)
        P1IFG = 0x00;                   // clear flag just in case anything happened before
	P1IE |= BIT6;			// enable interupt on ECHO pin
	P1IES &= ~BIT6;			// rising edge on ECHO pin
       __delay_cycles(30000);          // delay for 30ms (after this time echo times out if there is no object detected)
        distance = sensor/58;           // converting ECHO length into cm
        if(distance < 30 && distance != 0) {
          P1OUT |= BIT0;
          move++;
          time_motor = miliseconds;
          P2OUT |= (BIT4 + BIT5);
        }
      else { 
          P1OUT &= ~BIT0;
          move = 0;
          P2OUT |= (BIT5);
          P2OUT &= ~(BIT4);
  }
}



int get_move_value(){
  return move;
}

void setNoTurns(int nTurns) {
  turn = nTurns;
}

int getNoTurns() {
  return turn;
}

void setMoveVal(int mVal) {
  move = mVal;
  time_motor = miliseconds;
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  if(P1IFG&BIT6){  //is there interrupt pending?{
    if(!(P1IES&BIT6)) // is this the rising edge?
          {			
            TA1CTL|=TACLR;   // clears timer A
            miliseconds = 0;
            P1IES |= BIT6;  //falling edge
          }
          else
          {
            sensor = (long)miliseconds*1000 + (long)TAR;	//calculating ECHO length
          }
	P1IFG &= ~BIT6;	        //clear flag
  }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1 (void)
{
  miliseconds++;
  if (move > 0){
    if (((time_motor + 500) > miliseconds)){
      P2OUT |= (BIT3);
      P1OUT &= ~BIT7;
      P2OUT |= (BIT4);
      P2OUT &= ~(BIT5);   
    }
    else{
      move = 0;
      turn++;
      P2OUT |= (BIT3 + BIT4 + BIT5);
      P1OUT |= BIT7;
    }
  }
}

	

