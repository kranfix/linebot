// Project libries
#include "config.h"
#include "sleep.h"

#include <RTClibExtended.h>

// ARIOT libraries
#include <encodermotor.h>
#include <hcsr04.h>
#include <tictoc.h>
#include "linebot.h"
#include "lbProcesses.h"

//Tictoc tt(millis);
unsigned long start, now;

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
  //tt.tic();
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
int backLevel = 0;  
int frontLevel = 0;
void loop() {
  lb.processEvents();
  
  //float dist = hc.loop();
  float dist = 0;
  int batLevel = analogRead(batPin);
  float batV = batLevel * V5 / 1023;
  
  // Async report task
  //tt.tic();
  now = millis();
  if (now-start >= 5000 || asleeping) {
    //tt.tic();
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
      Serial.print(em.encoderPosition);
      Serial.print(",");
      Serial.print(em.getLong());
    Serial.println("]}");
  }
  asleeping = false;

  lb.processEvents();
  
  c = 'x';
  if(rtcPressed){
    rtcPressed = false;
  } else if(buttonPressed){
    buttonPressed = false;
  }

  if(Serial.available() > 0){
    c = Serial.read();
  }

  lb.processEvents();

  // Configuring linebot task list
  switch (c) {
    case 'x':
      break;
    case 'R':
      em.setEncoder(0);
    case 'S': // Stop
      goto InitSleepNow;
    case 'F': // Forward
      lb.setTaskList(FET,1);
      break;
    case 'B': // Backward
      lb.setTaskList(BTE,1);
      break;
    case 'A': // automatic along all the wire
      lb.setTaskList(defaultLbTask,NumOfTask);
      break;
    case 'X': // Atumatic with limit
      lb.setTaskList(simpleMiddleAutomatic,2);
      break;
  }

  lb.processEvents();

  // Verifying risk of poweroff
  if(riskOfPoweroff){
    if(batLevel > batLevel2){
      riskOfPoweroff = false;
    }
  } else if(batLevel < batLevel1){
    lb.saveData();
    riskOfPoweroff = true;
  }

  // Taking decision based on the risk of power off
  if(!riskOfPoweroff && !lb.execTask()){
    return;
  }
  
InitSleepNow:
  digitalWrite(activatorPin,LOW);
  em.setMotor(Action::Stop,em.getLong());
  delay(100);
  
  sleepNow();
  
  RTC.armAlarm(1, false);
  RTC.clearAlarm(1);
  RTC.alarmInterrupt(1, true);

  digitalWrite(activatorPin,HIGH);
  delay(3);
  asleeping = true;
  //tt.tic();
  start = millis;
}
