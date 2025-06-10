/*
  Blink INT1

  Switches the built-in LED on and off.
  Uses 16bit Timer 1 and compare match A interrupt vector to 
  blink the LED at one time for second (8MHz internal clock).
  This sketch will use about 164 bytes of the program memory space.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#define LEDPIN PIN_A4   //TINYx4 has the LED on the SPI CLK pin


void setup() {
  // initialize digital pin LEDPIN as an output.
  pinMode(LEDPIN, OUTPUT);

  cli();
  //reset the Timer 1 registers to 0
  TCCR1A = 0;
  TCCR1B = 0;

  OCR1A = 7812; // set the match register
  TCCR1B |= (1 << WGM12); // set the CTC mode bit

  // set the f/1024 clock prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

  TIMSK1 |= (1 << OCIE1A);  // set the compare match interrupt
  sei();
}


void loop() {
  //nothing here
}


//set the interrupt handler
ISR(TIMER1_COMPA_vect)
{
     digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
