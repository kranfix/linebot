#include "config.h"
#include "movement.h"
#include "hcsr04.h"
#include <RTClibExtended.h>
#include <EEPROM.h>

unsigned long now, start;
RTC_DS3231 RTC;
hcsr04_t hc;

void setup(){
  Serial.begin(9600);
  moveSetup(MotorForward,MotorBackward,IrForward,IrBackward,DetectionLevel);
  encoderSetup(Encoder);
  hc = hcsr04_CreateAndBegin(Trigger,Echo);


  //Wire.begin();
  RTC.begin();
#ifdef CLEAREEPROM
  Serial.println("Iniciando borrado de ");
  for (int i = 0 ; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  delay(100);
  Serial.println("Limpiado de EEPROM terminado.");
  Serial.println("Reprogramar sin la constante CLEAREEPROM");
  for(;;);
#else
  if(EEPROM.read(RtcSetDir) == 0){
    RTC.adjust(DateTime(__DATE__, __TIME__));
    EEPROM.write(RtcSetDir, 1);
    
    /*for(int i = 0; i < 5; i++){
      delay(1000);
      DateTime now = RTC.now();
    
      Serial.print(now.year(), DEC);
      Serial.print('/');
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.print(now.day(), DEC);
      Serial.print(' ');
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.println();
    }*/
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
  RTC.setAlarm(0xC, 30, 20, 18, 0);   //set your wake-up time here
  RTC.alarmInterrupt(1, true);
  
  setupWakeUp();
  
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
