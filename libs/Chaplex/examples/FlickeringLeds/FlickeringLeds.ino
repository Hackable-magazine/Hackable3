/* Example 1 for Chaplex - a library to control charlieplexed leds
 * *** randomly flickering leds ***
 * 
 * using minimal multiplex steps to controll all leds
 * 
 * author Stefan Götze
 * version 1.0
 *
 * tested with Arduino Uno and ATTiny85
 */
 
#include "Chaplex.h"

byte ctrlpins[] = {2,3,4};    //Arduino pins controlling charlieplexed leds
#define PINS 3                //number of these pins 

#define NEWPATTERN 100        //100 ms for new LED pattern

Chaplex myCharlie(ctrlpins, PINS);     //control instance

charlieLed myLeds[6]  = {{ 0 , 1 },    //controlled leds in sorted order
                         { 0 , 2 },    // every element is one led with 
                         { 1 , 2 },    // {anode-pin,cathode-pin}
                         { 2 , 1 },    // "pin" means here - index in ctrlpins
                         { 2 , 0 },    // array defined above
                         { 1 , 0 }};
                         
long goneTime;

void setup() {
  randomSeed(analogRead(0));  
  goneTime = millis();
}

void loop() {
  if (millis()-goneTime >= NEWPATTERN) {
    for (byte i=0; i<10; i++)
      myCharlie.ledWrite(myLeds[i], (byte)random(0,2));
    goneTime = millis();
  }
  myCharlie.outRow();
}
