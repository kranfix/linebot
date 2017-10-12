#include "movements.h"

void setup_movement(){
  // Right servo
  pinMode(servoRight_ena,OUTPUT);
  pinMode(servoRightPin,OUTPUT);

  // Left servo
  pinMode(servoLeft_ena,OUTPUT);
  pinMode(servoLeftPin,OUTPUT);
}

void ServoStop(){
  // Turning off PWM
  analogWrite(servoRightPin,0);
  analogWrite(servoLeftPin,0);

  // Disabling server power supplier
  digitalWrite(servoRight_ena,LOW);
  digitalWrite(servoLeft_ena,LOW);
}


// Level: the level over or below the
// stop offset to set a forward or
// backward movement
void ServoMove(int8_t level){
  // Enabling servo power supplier
  digitalWrite(servoRight_ena,HIGH);
  digitalWrite(servoLeft_ena,HIGH);

  // Using the stop offset to move
  // forward or backward
  analogWrite(servoRightPin,servoRightStopOffset + level);
  analogWrite(servoLeftPin,servoLeftStopOffset - level);
}
