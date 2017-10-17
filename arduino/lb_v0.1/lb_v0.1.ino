#include "config.h"
#include "movements.h"

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  //time_setup();
  ServoSetup();
  pinMode(RPiCapturePin,OUTPUT);
}

void loop(){
  if(xbeeSerial.available() > 0){
    char in = xbeeSerial.read();
    switch(in){
      case 'F': // Forward
        ServoMove(50);
        Serial.println("Moving Forward");
        xbeeSerial.write('A');
        break;

      case 'B': // Backward
        ServoMove(-50);
        Serial.println("Moving Backward");
        xbeeSerial.write('A');
        break;

      case 'S': // Stop
        ServoStop();
        Serial.println("Stop");
        xbeeSerial.write('A');
        break;

      case 'C': // Stop
        digitalWrite(RPiCapturePin,HIGH);
        delay(500);
        Serial.println("Capturing");
        xbeeSerial.write('A');
        digitalWrite(RPiCapturePin,LOW);
        break;
    }
  }
}
