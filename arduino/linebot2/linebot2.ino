#include "config.h"
#include "movement.h"

unsigned long now, start;

void setup(){
  Serial.begin(9600);
  moveSetup(MotorForward,MotorBackward,IrForward,IrBackward,DetectionLevel);

  start = millis();
}

void loop(){
  if(Serial.available() > 0){
    char c = Serial.read();
    switch (c) {
      case 'S':
        moveSet(MOVE_STOP);
        Serial.write('s');
        break;
      case 'F':
        moveSet(MOVE_FORWARD);
        Serial.write('f');
        break;
      case 'B':
        moveSet(MOVE_BACKWARD);
        Serial.write('b');
        break;
      default:
        Serial.write('d');
        break;
    }
  }
  moveLoop();

  now = millis();
  if(now - start >= 500){
    Serial.println(analogRead(IrForward));
    start = now;
  }
}
