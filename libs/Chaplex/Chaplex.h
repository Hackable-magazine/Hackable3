/*
||
|| @author Stefan Götze 
||         using Alexander Brevig - Charlieplex library
|| @version 0.1
||
*/

#ifndef Chaplex_h
#define Chaplex_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ON 1
#define OFF 0

struct CharlieLed {
  byte r;
  byte c; 
} ;

typedef struct CharlieLed charlieLed;

class Chaplex {

public:
	Chaplex(byte* userPins,byte numberOfUserPins);
	
	void ledWrite(charlieLed led, byte state);
	void allClear();
	void outRow();
	
private:
	byte numberOfPins;
	byte* pins;
	byte* ledCtrl;
    volatile byte ledRow;
};

#endif
