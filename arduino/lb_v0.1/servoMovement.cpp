#include "config.h"
#include "movements.h"
#include <Arduino.h>

void ServoSetup(){
  pinMode(servoEnablePin,OUTPUT);
  pinMode(servoRightPin,OUTPUT); // Right servo
  pinMode(servoLeftPin,OUTPUT);  // Left servo
}

void ServoStop(){
  // Turning off PWM
  analogWrite(servoRightPin,0);
  analogWrite(servoLeftPin,0);

  // Disabling server power supplier
  digitalWrite(servoEnablePin,LOW);
}


// Level: the level over or below the
// stop offset to set a forward or
// backward movement
void ServoMove(char level){
  // Enabling servo power supplier
  digitalWrite(servoEnablePin,HIGH);

  // Using the stop offset to move
  // forward or backward
  analogWrite(servoRightPin,servoRightStopOffset + level);
  analogWrite(servoLeftPin,servoLeftStopOffset - level);
}
