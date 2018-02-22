#include "linebot.h"
#include <Arduino.h>
#include <EEPROM.h>

LineBot::LineBot(EncoderMotor *em, uint8_t frontTop, uint8_t backTop, int level){
  // Encode-Motor
  this->em = em;

  // Infrared
  irFrontTop = frontTop;
  irBackTop  = backTop;  
  irLevel    = level;

  processEvents();
}

void LineBot::processEvents(){
  em->loop();
  int backLevel = analogRead(irBackTop);  
  int frontLevel = analogRead(irFrontTop);
  eventBack  = (backLevel >= irLevel);
  eventFront = (frontLevel >= irLevel);
}

void LineBot::setTaskList(lbTask_t *lbt, uint8_t len){
  index = 0;
  this->lbt = lbt;
  this->len = len;
#ifdef LbDebug
  Serial.print("Secuencia: ");
  Serial.print(index);
  Serial.print("/");
  Serial.println(len);
#endif
}

bool LineBot::execTask(){
  lbTask_t *t = &lbt[index]; // current task
  bool next = false;

  Action act = t->action;
  em->setMotor(act,t->limit);
  if(act == Action::Stop){
    em->setLong(t->limit);
    goto NextTask;
  } else {
    bool back  = (act == Action::Backward);
    bool front = (act == Action::Forward);
    bool irEvent = (eventFront & front) || (eventBack  & back);
  
    if(irEvent){
#ifdef LbDebug
      Serial.print("IR:(f,b)=(");
      Serial.print(eventFront);
      Serial.print(",");
      Serial.print(eventBack);
      Serial.println(")");
#endif
      if(t->top){
        goto NextTask;
      } else {
        return true; // Only a Pause
      }
    } else if(em->event && !t->top){
      goto NextTask;
    }
  }

  // Continue without Sleep
  return false;

  // module for index task if necessary
  NextTask:
  index++;
  if(index == len){
    index = 0;
  }
#ifdef LbDebug
  Serial.print("Secuencia: ");
  Serial.print(index);
  Serial.print("/");
  Serial.println(len);
#endif
  return (t->trans == lbTrans::Sleep);
}

void LineBot::saveData(){
  // Saving lbt in EEPROM
  lbStore_t data = {
    true, // EEPROM flag for recover
    lbt,index,len,
    em->encoderPosition
  };
  uint8_t N = sizeof(data);
  uint8_t *buf = (uint8_t*)(&data);
  
  for(uint8_t i = 0; i < N; i++){
    EEPROM.write(i,buf[i]);    
  }
}


bool LineBot::recoverData(){
  if(lbt != NULL){
    return false;
  }

  // Reading saved data
  lbStore_t data;
  uint8_t N = sizeof(lbStore_t);
  uint8_t *buf = (uint8_t*)(&data);

  for(uint8_t i = 0; i < N; i++){
    buf[i] = EEPROM.read(i);    
  }

  // Verifying if there's data to recover
  if(data.recover){
    lbt = data.lbt;
    index = data.index;
    len = data.len;
    em->setEncoder(data.encoderPosition);
  }
  return true;
}

void LineBot::resetData(){
  uint8_t N = sizeof(lbStore_t);

  for(uint8_t i = 0; i < N; i++){
    EEPROM.write(i,0);    
  }
}

