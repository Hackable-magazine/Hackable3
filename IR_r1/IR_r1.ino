#include <IRremote.h>

int RECV_PIN = 11;
int led = 12;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == RC6) {
      Serial.print("RC5: ");
      Serial.println(results.value, HEX);
      if(results.value == 0x800F045B || results.value == 0x800F845B)
        digitalWrite(led, HIGH);
      if(results.value == 0x800F045C || results.value == 0x800F845C)
        digitalWrite(led, LOW);
      /*
      if(results.value == 0x800F840C)
        digitalWrite(led, HIGH);
      if(results.value == 0x800F040C)
        digitalWrite(led, LOW);
      */
      // no toogle !!!! tosh tosh 800F040F!=800F840F  0->8 8->0
      if(results.value == 0x800F840C || results.value == 0x800F040C) {
        digitalWrite(led, !digitalRead(led));  // toggle
        delay(500);
      }
    }
    irrecv.resume(); // Receive the next value
  }
}



