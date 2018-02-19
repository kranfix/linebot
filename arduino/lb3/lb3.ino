#include "config.h"
#include "movement.h"
#include "sleep.h"
#include <RTClibExtended.h>
#include <EEPROM.h>

// ARIOT libraries
#include <encodermotor.h>
#include <hcsr04.h>

unsigned long now, start;
RTC_DS3231 RTC;
HCSR04 hc(Trigger, Echo, 343e-4*1.2);

void setup() {
  moveSetup(MotorForward, MotorBackward, IrForward, IrBackward, DetectionLevel);
  encoderSetup(Encoder);

  //Wire.begin();
  RTC.begin();
#ifdef CLEAREEPROM
  Serial.begin(9600);
  Serial.println("Iniciando borrado de ");
  for (int i = 0 ; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  delay(100);
  Serial.println("Limpiado de EEPROM terminado.");
  Serial.println("Reprogramar sin la constante CLEAREEPROM");
  for (;;);
#else
  if (EEPROM.read(RtcSetDir) == 0) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
    EEPROM.write(RtcSetDir, 1);
  }
#endif

  //clear any pending alarms
  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, false);
  RTC.armAlarm(2, false);
  RTC.clearAlarm(2);
  RTC.alarmInterrupt(2, false);

  //Set SQW pin to OFF (in my case it was set by default to 1Hz)
  //The output of the DS3231 INT pin is connected to this pin
  //It must be connected to arduino D2 pin for wake-up
  RTC.writeSqwPinMode(DS3231_OFF);

  //Set alarm1 every day at 18:33
  RTC.setAlarm(0xE, 15, 20, 01, 0);   //set your wake-up time here
  RTC.alarmInterrupt(1, true);

  setupWakeUp();
}

int N = 700.0 * Slots / (PI * Diameter);
char c = 0;

int serialActived = 0;
void loop() {
  if (!serialActived) {
    Serial.begin(9600);
    serialActived = 1;
    delay(10);
    start = millis();
  }
  c = 0;
  if (buttonPressed) {
    c = 'S';
  } else if (Serial.available() > 0) {
    c = Serial.read();
  }

  switch (c) {
    case 0:
      break;
    case 'S': // Stop
      moveSet(MOVE_STOP);
      Serial.write('s');
      initSleep = 1;
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
  encoderSetForwardLimit(N);
  moveLoop();

  now = millis();
  if (now - start >= 10000) {
    start = now;

    float dist = hc.loop();
    float bat = analogRead(Mq2) * V5 / 1023;
    Serial.print("{\"HC-SR04\": ");
    Serial.print(dist);
    Serial.print(",\"Bat\": " );
    Serial.print(bat);
    Serial.print(",\"Encoder\": ");
    Serial.print( digitalRead(Encoder));
    Serial.print(",\"Counter\": ");
    Serial.print(encoderCounter());
    Serial.println("}");
    delay(10);
  }

  if (initSleep) {
    initSleep = 0;
    lbActive = 0;

    Serial.end();
    serialActived = 0;

    sleepNow();
    RTC.armAlarm(1, false);
    RTC.clearAlarm(1);
    RTC.alarmInterrupt(1, true);
  }
}
