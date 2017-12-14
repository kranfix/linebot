#include <Arduino.h>
#include "hcsr04.h"

hcsr04_t hcsr04_CreateAndBegin(int trigger, int echo){
  hcsr04_t hc = hcsr04_new(trigger,echo);
  hcsr04_begin(&hc);
  return hc;
}

hcsr04_t hcsr04_new(int trigger, int echo){
  return {trigger, echo, 0};
}

void hcsr04_begin(hcsr04_t * hc){
  pinMode(hc->trigger,OUTPUT);
  pinMode(hc->echo,INPUT);
  digitalWrite(hc->trigger, LOW);
  hc->isActive = 1;
}

float hcsr04_loop(hcsr04_t * hc){
  digitalWrite(hc->trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(hc->trigger, LOW);

  int time = pulseIn(hc->echo, HIGH) / 2;
  return time * 343e-4 * 1.2; // cm   // calibration scale: 1.2
}

