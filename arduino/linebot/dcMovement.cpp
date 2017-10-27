#include "config.h"
#include "movements.h"
#include <Arduino.h>

void DcSetup(){
  pinMode(dcEnablePin,OUTPUT);
  pinMode(dcRightPin,OUTPUT); // Right servo
  pinMode(dcLeftPin,OUTPUT);  // Left servo
}

void DcStop(){
  // Turning off PWM
  analogWrite(dcRightPin,0);
  analogWrite(dcLeftPin,0);

  // Disabling server power supplier
  digitalWrite(dcEnablePin,LOW);
}

// Level: the level over or below the
// stop offset to set a forward or
// backward movement
void DcMove(char level){
  // Enabling servo power supplier
  digitalWrite(dcEnablePin,HIGH);

  // Using the stop offset to move
  // forward or backward
  analogWrite(dcRightPin,servoRightStopOffset + level);
  analogWrite(dcLeftPin,servoLeftStopOffset - level);
}
