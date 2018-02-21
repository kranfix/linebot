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
  RTC.setAlarm(wakeUpFreq, 15, 20, 01, 0);   //set your wake-up time here
  RTC.alarmInterrupt(1, true);

  Serial.begin(9600);
  delay(10);
  start = millis();
  digitalWrite(activatorPin,HIGH);
  
  setupWakeUp();

  // Recover LineBot Data from EEPROM if necessary
  //if(!lb.recoverData()){
    lb.setTaskList(defaultLbTask,NumOfTask);
  //}

  asleeping = true;
}

char c = 0;
void loop() {
  lb.processEvents();
  float dist = hc.loop();
  int batLevel = analogRead(batPin);
  float batV = batLevel * V5 / 1023;
  
  // Async report task
  now = millis();
  if (now - start >= 2000 || asleeping) {
    start = now;
    Serial.print("{\"type\":\"lb3\",");
    Serial.print("\"id\":");
    Serial.print(ID);
    Serial.print(",\"HC-SR04\": ");
      Serial.print(dist);
    Serial.print(",\"Bat\":[" );
      Serial.print(batLevel);
      Serial.print(",");
      Serial.print(batV);
      Serial.print("]");
    Serial.print(",\"pos\":[");
      Serial.print(digitalRead(EncoderPin));
      Serial.print(",");
      Serial.print(em.getEncoder());
      Serial.print(",");
      Serial.print(em.getLong());
    Serial.print("],\"dist\":");
    Serial.print(dist);
    Serial.println("}");
    start = now;
    delay(10);
  }
  asleeping = false;
  
  c = 'Z';
  if(rtcPressed){
    rtcPressed = false;
  } else if(buttonPressed){
    buttonPressed = false;
    if(Serial.available() > 0){
      c = Serial.read();
    }
  }

  // Configuring linebot task list
  switch (c) {
    case 'S': // Stop
      goto InitSleepNow;
      break;
    case 'F': // Forward
      lb.setTaskList(FTE,1);
      break;
    case 'B': // Backward
      lb.setTaskList(BTE,1);
      break;
    case 'A': // automatic along all the wire
      lb.setTaskList(simpleAutomatic,2);
      break;
    case 'X': // Atumatic with limit
      lb.setTaskList(simpleMiddleAutomatic,2);
      break;
    case 'R': // Reset
      lb.setTaskList(justSleep,1);
      em.setEncoder(0);
      break;
  }

  // Verifying risk of poweroff
  if(riskOfPoweroff){
    if(batLevel > batLevel2){
      riskOfPoweroff = false;
    }
  } else if(batLevel < batLevel1){
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
  //return;
  digitalWrite(activatorPin,LOW);
  delay(100);
  
  sleepNow();

  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);
  
  digitalWrite(activatorPin,HIGH);
  delay(3);
  asleeping = true;
  start = millis();
}
