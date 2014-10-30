#include <IRremote.h>

int RECV_PIN = 11;

int chien = 10;
int chat = 9;
int canard = 8;
int cheval = 7;
int chevre = 6;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(chien, OUTPUT);
  pinMode(chat, OUTPUT);
  pinMode(canard, OUTPUT);
  pinMode(cheval, OUTPUT);
  pinMode(chevre, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == RC6) {
      switch(results.value) {
        case 0x800F045B:
        case 0x800F845B:
          digitalWrite(chien, HIGH);
          break;
        case 0x800F045C:
        case 0x800F845C:
          digitalWrite(chat, HIGH);
          break;
        case 0x800F045D:
        case 0x800F845D:
          digitalWrite(canard, HIGH);
          break;
        case 0x800F045E:
        case 0x800F845E:
          digitalWrite(cheval, HIGH);
          break;
        case 0x800F0422:
        case 0x800F8422:
          digitalWrite(chevre, HIGH);
          break;
      }
      delay(10);
      digitalWrite(chien,  LOW);
      digitalWrite(chat,   LOW);
      digitalWrite(canard, LOW);
      digitalWrite(cheval, LOW);
      digitalWrite(chevre, LOW);
    }
    irrecv.resume();
  }
}



