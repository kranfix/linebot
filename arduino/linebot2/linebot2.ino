#include "config.h"
#include "movement.h"
#include "hcsr04.h"

unsigned long now, start;

hcsr04_t hc;

void setup(){
  Serial.begin(9600);
  moveSetup(MotorForward,MotorBackward,IrForward,IrBackward,DetectionLevel);
  encoderSetup(Encoder);
  hc = hcsr04_CreateAndBegin(Trigger,Echo);
  start = millis();
}

int N = 700.0 * Slots / (PI * Diameter);

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
        N = 700.0 * Slots / (PI * Diameter);
        Serial.write('f');
        break;
      case 'B':
        moveSet(MOVE_BACKWARD);
        Serial.write('b');
        break;
      case 'A':
        moveSet(MOVE_AUTO);
        Serial.write('a');
        break;
      case 'X':
        moveSet(MOVE_FORWARD);
        N = Distance * Slots / (PI * Diameter);
        Serial.write('x');
        break;
      default:
        Serial.write('d');
        break;
    }
  }
  encoderSetForwardLimit(N);
  moveLoop();

  now = millis();
  if(now - start >= 500){
    start = now;
    /*Serial.print("IR Forward: ");
    Serial.println(analogRead(IrForward));
    Serial.print("IR Backward: ");
    Serial.println(analogRead(IrBackward));*/
    
    float d = hcsr04_loop(&hc);
    Serial.print("HC-SR04:\t");
    Serial.println(d);

    Serial.print("MQ2:\t\t");
    Serial.println(analogRead(Mq2));

    Serial.print("Encoder:\t");
    Serial.print(digitalRead(Encoder));
    Serial.print("  ");
    Serial.println(encoderCounter());
  }
}
