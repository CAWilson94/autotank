#include <msp430.h>

/*Movement Header File*/
void configure_pins();
void move_body_forward();
void move_body_backwards();
void turn_body_right(double);
void turn_body_left(double);
void rotate_180_right();
void rotate_180_left();