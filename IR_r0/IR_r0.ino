#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    switch(results.decode_type) {
      case UNKNOWN:
        Serial.print("UNKNOWN: ");
        break;
      case RC6:
        Serial.print("RC6: ");
        break;
      case RC5:
        Serial.print("RC5: ");
        break;
      case NEC:
        Serial.print("NEC: ");
        break;
      case SONY:
        Serial.print("SONY: ");
        break;
      case LG:
        Serial.print("LG: ");
        break;
      case JVC:
        Serial.print("JVC: ");
        break;
      case PANASONIC:
        Serial.print("PANASONIC: ");
        Serial.print(results.panasonicAddress,HEX);
        Serial.print(" - ");
        break;
      default:        
        Serial.print("???: ");
    }
    
    Serial.print(results.value, HEX);
    Serial.print(" ");
    Serial.print(results.bits, DEC);
    Serial.println(" bits");
    irrecv.resume();
  }
}



