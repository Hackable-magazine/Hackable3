#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

#include <Chaplex.h>

byte ctrlpins[] = {2,3,4,5};

Chaplex myCharlie(ctrlpins, 4);

charlieLed myLeds[12]={{0,1},
                       {1,0},
                       {0,2},
                       {2,0},
                       {1,2},
                       {2,1},
                       {0,3},
                       {3,0},
                       {1,3},
                       {3,1},
                       {2,3},
                       {3,2}};


byte timer2TCNT2 = 178;    //preload timer 256-16MHz/1024/78 = near 5 ms

void setup() {
  for (int i=0; i< 12; i++) {           
    myCharlie.ledWrite(myLeds[i], OFF);
    delay(100);
  }
  
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
  tmElements_t tm;
  if (RTC.read(tm)) {
    for(int i=0; i<5; i++) {
      myCharlie.ledWrite(myLeds[4-i], (tm.Hour & (1 << i)));
    }
    myCharlie.ledWrite(myLeds[5], OFF);
    for(int i=0; i<6; i++) {
      myCharlie.ledWrite(myLeds[11-i], (tm.Minute & (1 << i)));
    }
  }
  delay(500);
}

