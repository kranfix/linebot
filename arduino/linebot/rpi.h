#include <arduino.h>
#include "config.h"
#include "modes.h"

void RpiSetup(){
  pinMode(RPiConfirmedPin,INPUT);
  pinMode(RPiCapturePin,OUTPUT);
}

void RpiCamCapture() {
  digitalWrite(RPiCapturePin,HIGH);
  for(modes_tic(); modes_toc() - > )
}
