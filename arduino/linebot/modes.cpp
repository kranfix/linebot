#include "cofig.h"
#include "modes.h"
#include <arduino.h>

unsigned long now, ref;

void modes_tic() {
  ref = millis();
  now = millis();
}

bool modes_toc(unsigned long interval) {
  now = millis();
  return now - ref;
}

void modes_delay(int lapse) {
  modes_tic();
  while(modes_toc() < lapse) {
    if(xbeeSerial.available()){
      char c = xbeeSerial.read();
      xbeeSerial.write(AT_Rejected);
      Serial.Println("Request rejected by Automatic Process");
    }
  }
}
