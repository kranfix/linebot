#include "movement.h"
#include <Arduino.h>

int F, B, f, b, level;
int status, lastStop = MOVE_STOP;

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
    lastStop = MOVE_FORWARD;
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
    lastStop = MOVE_BACKWARD;
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
    case MOVE_AUTO:
      moveAutomatic();
      break;
  }
}

void moveAutomatic(){
  switch(lastStop){
    case MOVE_STOP:
    case MOVE_BACKWARD:
      moveForward();
      break;
    case MOVE_FORWARD:
      moveBackward();
      break;
  }
  status = MOVE_AUTO;
}

