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
      case 'S': // Stop
        moveSet(MOVE_STOP);
        Serial.write('s');
        break;
      case 'F': // Forward
        moveSet(MOVE_FORWARD);
        N = 700.0 * Slots / (PI * Diameter);
        Serial.write('f');
        break;
      case 'B': // Backward
        moveSet(MOVE_BACKWARD);
        Serial.write('b');
        break;
      case 'A': // automatic along all the wire
        moveSet(MOVE_AUTO);
        N = 700.0 * Slots / (PI * Diameter);
        Serial.write('a');
        break;
      case 'X': // Atumatic with limit
        //moveSet(MOVE_FORWARD);
        moveSet(MOVE_AUTO);
        N = Distance * Slots / (PI * Diameter);
        Serial.write('x');
        break;
      case 'R': // Reset
        moveSet(MOVE_STOP);
        encoderReset();
        Serial.write('r');
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
    /*Serial.println();
    Serial.print("IR Forward: ");
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
    Serial.println();
  }
}
