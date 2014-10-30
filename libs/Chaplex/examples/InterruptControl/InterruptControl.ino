/* Example 2 for Chaplex - a library to control charlieplexed leds
 * *** controlling led bar with output via timer2 interrupt ***
 * 
 * using minimal multiplex steps to control all leds
 * 
 * author Stefan Götze
 * version 1.0
 *
 * only tested with Arduino Uno
 */
 
#include "Chaplex.h"

byte ctrlpins[] = {2,3,4};    //Arduino pins controlling charlieplexed leds
#define PINS 3                //number of these pins 

#define DELAY 100             //speed of switching leds in bar on and off

Chaplex myCharlie(ctrlpins, PINS);     //control instance

charlieLed myLeds[6]  = {{ 0 , 1 },    //leds of bar in sorted order
                         { 0 , 2 },    // every element is one led with 
                         { 1 , 2 },    // {anode-pin,cathode-pin}
                         { 2 , 1 },    // "pin" means here - index in ctrlpins
                         { 2 , 0 },    // array defined above
                         { 1 , 0 }};

byte timer2TCNT2 = 178;    //preload timer 256-16MHz/1024/78 = near 5 ms

void setup() {
  // initialize timer2 
  noInterrupts();                 //disable all interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = timer2TCNT2; 
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  //prescaler 1024 = 64 micro secs
  TIMSK2 |= (1 << TOIE2);        //enable timer overflow interrupt
  interrupts();                  //enable all interrupts
}

ISR(TIMER2_OVF_vect) {          //timer2 interrupt routine
  myCharlie.outRow();           //output for one led row
  TCNT2 = timer2TCNT2;          //preload timer for next interrupt
}

void loop() {
  for (int i=0; i< 10; i++) {           
    myCharlie.ledWrite(myLeds[i], ON);
    delay(DELAY);
  }
  for (int i=0; i<10; i++) {
    myCharlie.ledWrite(myLeds[i], OFF);
    delay(DELAY);
  }
}

