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
  eventBack  = (analogRead(irBackTop)  >= irLevel);
  eventFront = (analogRead(irFrontTop) >= irLevel);
}

void LineBot::setTaskList(lbTask_t *lbt, uint8_t len){
  index = 0;
  this->lbt = lbt;
  this->len = len;
}

bool LineBot::execTask(){
  lbTask_t *t = &lbt[index]; // current task
  bool activateSleep = (t->trans == lbTrans::Sleep);

  Action act = em->getAction();
  if(act == Action::Stop){
    em->setLong(t->limit);
    index++;
  } else if(act == Action::Stop){
    index++;
  } else {
    bool back  = (act == Action::Backward);
    bool front = (act == Action::Forward);
    bool irEvent = (eventFront & front) || (eventBack  & back);
  
    if(irEvent){
      if(t->top){
        index++; // Next task
      } else {
        activateSleep = true; // Only a Pause
      }
    } else if(em->encoderEvent() && !t->top){
      index++;  // Next task
    }
  }

  // module for index task if necessary
  if(index == len){
    index = 0;
  }
  return activateSleep;
}

void LineBot::saveData(){
  // Saving lbt in EEPROM
  lbStore_t data = {
    true, // EEPROM flag for recover
    lbt,index,len,
    em->getEncoder()
  };
  uint8_t N = sizeof(data);
  uint8_t *buf = (uint8_t*)(&data);
  
  for(int i = 0; i < N; i++){
    EEPROM.write(i,buf[i]);    
  }
}


bool LineBot::recoverData(){
  if(lbt != NULL){
    return;
  }

  // Reading saved data
  lbStore_t data;
  uint8_t N = sizeof(data);
  uint8_t *buf = (uint8_t*)(&data);

  for(int i = 0; i < N; i++){
    buf[i] = EEPROM.read(i);    
  }

  // Verifying if there's data to recover
  if(data.recover){
    lbt = data.lbt;
    index = data.index;
    len = data.len;
    em->setEncoder(data.encoderPosition);
  }
}

void LineBot::resetData(){
  
}

