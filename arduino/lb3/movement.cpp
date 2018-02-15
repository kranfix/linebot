#include "movement.h"
#include <Arduino.h>

int F, B, f, b, level, encoder;
int encoderLimit;

int mode = MOVE_STOP;
int status = MOVE_STOP;
int lastStop = MOVE_STOP;

int encoderNow, encoderLast, encoderCount;

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

void encoderSetup(int _encoder){
  encoder = _encoder;
  pinMode(encoder,INPUT);
  encoderNow = digitalRead(encoder);
  encoderLast = encoderNow;
  encoderCount = 0;
}

void moveForward(){
  int Fval = HIGH;
  int Bval = LOW;
  status = MOVE_FORWARD;
  if(analogRead(f) >= level){
    moveSet(MOVE_STOP);
    lastStop = MOVE_FORWARD;
    Fval = LOW;
  }
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveBackward(){
  status = MOVE_BACKWARD;
  int Fval = LOW;
  int Bval = HIGH;  
  if(analogRead(b) >= level){
    lastStop = MOVE_BACKWARD;
    moveSet(MOVE_STOP);
    Bval = LOW;
    encoderReset();
  }
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveStop(){
  status = MOVE_STOP;
  int Fval = LOW;
  int Bval = LOW;
  digitalWrite(F,Fval);
  digitalWrite(B,Bval);
}

void moveSet(int _mode){
  mode = _mode;
  if(mode != MOVE_AUTO){
    status = mode;
  }
}

void encoderSetForwardLimit(int N){
  encoderLimit = N;
}

void moveLoop(){
  if(status == MOVE_FORWARD && encoderCount >= encoderLimit){
    lastStop = MOVE_FORWARD;
  }
  
  switch(mode){
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

  // Encoder section
  encoderNow = digitalRead(encoder);
  if(encoderNow != encoderLast){
    if(status == MOVE_FORWARD){
      encoderCount++;
    } else if (status == MOVE_BACKWARD){
      encoderCount--;
    }
  }
  encoderLast = encoderNow;
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
  mode = MOVE_AUTO;
}

int encoderCounter(){
  return encoderCount;
}

void encoderReset(){
  encoderCount = 0;
}
