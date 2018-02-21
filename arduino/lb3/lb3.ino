// Project libries
#include "config.h"
#include "sleep.h"

#include <RTClibExtended.h>
#include <EEPROM.h>

// ARIOT libraries
#include <encodermotor.h>
#include <hcsr04.h>
//#include <tictoc.h>
#include "linebot.h"
#include "lbProcesses.h"

unsigned long now, start;

RTC_DS3231 RTC;
HCSR04 hc(Trigger, Echo, 343e-4*1.2);
EncoderMotor em(EncoderPin,Slots,Diameter/2,{MotorForward,MotorBackward});
LineBot lb(&em,IrForward,IrBackward,IrDetectionLevel);

bool asleeping = false;
bool riskOfPoweroff = false;

void setup() {
  RTC.begin(); //implicit Wire.begin();
#ifdef CLEAREEPROM
  RTC.adjust(DateTime(__DATE__, __TIME__));
  Serial.begin(9600);
  Serial.println("Iniciando borrado de ");
  lb.resetData();
  delay(100);
  Serial.println("Limpiado de EEPROM terminado.");
  Serial.println("Reprogramar sin la constante CLEAREEPROM");
  for (;;);
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

  Serial.begin(9600);
  delay(10);
  start = millis();
  digitalWrite(activatorPin,HIGH);
  
  setupWakeUp();

  // Recover LineBot Data from EEPROM if necessary
  if(!lb.recoverData()){
    lb.setTaskList(defaultLbTask,NumOfTask); 
  }

  asleeping = true;
}

char c = 0;
void loop() {
  lb.processEvents();

  // Async report task
  now = millis();
  if (now - start >= 2000 || asleeping) {
    start = now;
    float dist = hc.loop();
    float bat = analogRead(batPin) * V5 / 1023;
    Serial.print("{\"HC-SR04\": ");
    Serial.print(dist);
    Serial.print(",\"Bat\": " );
    Serial.print(bat);
    Serial.print(",\"Encoder\": ");
    Serial.print(digitalRead(EncoderPin));
    Serial.print(",\"Counter\"=: ");
    Serial.print(em.getLong());
    Serial.println("}");
    start = now;
    delay(10);
  }
  asleeping = false;

  c = 0;
  if (buttonPressed && Serial.available() > 0) {
    c = Serial.read();
  }

  // Configuring linebot task list
  switch (c) {
    case 'S': // Stop
      lb.setTaskList(justSleep,1);
      Serial.write('s');
      break;
    case 'F': // Forward
      lb.setTaskList(FTE,1);
      Serial.write('f');
      break;
    case 'B': // Backward
      lb.setTaskList(BTE,1);
      Serial.write('b');
      break;
    case 'A': // automatic along all the wire
      lb.setTaskList(simpleAutomatic,2);
      Serial.write('a');
      break;
    case 'X': // Atumatic with limit
      lb.setTaskList(simpleMiddleAutomatic,2);
      Serial.write('x');
      break;
    case 'R': // Reset
      lb.setTaskList(justSleep,1);
      em.setEncoder(0);
      Serial.write('r');
      break;
    default:
      Serial.write('d');
      break;
  }

  // Verifying risk of poweroff
  if(riskOfPoweroff){
    if(analogRead(batPin) > batLevel2){
      riskOfPoweroff = false;
    }
  } else if(analogRead(batPin) < batLevel1){
    lb.saveData();
    riskOfPoweroff = true;
    goto InitSleepNow;
  }

  // Execution LineBot Task
  //bool goToSleep = lb.execTask(); 
  if(!lb.execTask()){
    return;
  }
 
InitSleepNow:
  digitalWrite(activatorPin,LOW);
  Serial.end();
  delay(100);
  
  sleepNow();

  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);
  
  Serial.begin(9600);
  digitalWrite(activatorPin,HIGH);
  delay(10);
  asleeping = true;
  start = millis();
}
