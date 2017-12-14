#include "movement.h"
#include <Arduino.h>

int F, B, f, b, level;
int status;

void moveSetup(int _F, int _B, int _f, int _b, int detectionLevel){
  F = _F;
  B = _B;
  f = _f;
  b = _b;
  level = detectionLevel;
  pinMode(F,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(f,INPUT);
  pinMode(b,INPUT);
}

void moveForward(){
  int Fval = HIGH;
  int Bval = LOW;
  if(analogRead(f) >= level){
    status = MOVE_STOP;
    Fval = LOW;
  }
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveBackward(){
  int Fval = LOW;
  int Bval = HIGH;
  if(analogRead(b) >= level){
    status = MOVE_STOP;
    Bval = LOW;
  }
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveStop(){
  int Fval = LOW;
  int Bval = LOW;
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveSet(int _status){
  status = _status;
}

void moveLoop(){
  switch(status){
    case MOVE_STOP:
      moveStop();
      break;
    case MOVE_FORWARD:
      moveForward();
      break;
    case MOVE_BACKWARD:
      moveBackward();
      break;
  }
}
