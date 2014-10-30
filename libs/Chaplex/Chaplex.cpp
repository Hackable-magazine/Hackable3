/*
||
|| @author Stefan Götze 
||         using Alexander Brevig - Charlieplex library
|| @version 0.1
||
*/

#include "Chaplex.h"

Chaplex::Chaplex(byte* userPins,byte numberOfUserPins){
	pins = userPins;
	numberOfPins = numberOfUserPins;
	ledCtrl = (byte *)malloc(sizeof(byte) * numberOfPins * numberOfPins);
	ledRow = 0;
	allClear();
	outRow();
}

// set control-array for one LED ON/OFF
void Chaplex::ledWrite(charlieLed led, byte state){
  	if ((led.r<numberOfPins) && (led.c<numberOfPins) && (led.r!=led.c)) 
    	*(ledCtrl+led.r*numberOfPins+led.c) = state;
}

//set control-array for all LEDs OFF
void Chaplex::allClear(){
  	for (byte i=0; i<numberOfPins; i++)
    	for (byte j=0; j<numberOfPins; j++)
      		*(ledCtrl+i*numberOfPins+j) = OFF;
}

// write control-array to LEDs of one row and set count (ledRow) to next
void Chaplex::outRow() {
	for (byte i=0; i<numberOfPins; i++) 
    	pinMode(pins[i],INPUT);
  
	pinMode(pins[ledRow],OUTPUT);
	digitalWrite(pins[ledRow],HIGH);

	for (byte i=0; i<numberOfPins; i++)  
    	if (*(ledCtrl+ledRow*numberOfPins+i)) {
      		pinMode(pins[i],OUTPUT);
      		digitalWrite(pins[i],LOW);
    	} 

	if (++ledRow >= numberOfPins)
    	ledRow = 0;
}
