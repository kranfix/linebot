/* Linebot program estructure */
#pragma once
#include <stdint.h>
#include <EEPROM.h>
#include "encodermotor.h"

// Linebot Transition type
enum class lbTrans : uint8_t {Nop, Sleep};

// Linebot Task
typedef struct {
  Action  action; // Encoder-Motor action
  float   limit;
  bool    top;   // Has the top more priority then encoder limit?
  lbTrans trans;
} lbTask_t;

class LineBot {
    // Encoder-Motor
    EncoderMotor *em;

    // Infrared sensors
    uint8_t irFrontTop;
    uint8_t irBackTop;
    int irLevel;
    uint8_t eventBack;  // bool
    uint8_t eventFront; // bool

    // LineBot Task List
    lbTask_t *lbt;
    uint8_t index;
    uint8_t len;

  public:
    LineBot(EncoderMotor *em, uint8_t frontTop, uint8_t backTop, int level);

    void processEvents();
    void Stop();
    void Sleep();

    // Linebot Task control
    void setTaskList(lbTask_t *lbt, uint8_t len);
    bool execTask(); // returns true if sleep mode has to be activated

    // Data Store
    void saveData();
    bool recoverData();
    void resetData();
};

typedef struct {
  bool recover;
  lbTask_t * lbt;
  uint8_t index;
  uint8_t len;
  int encoderPosition;
} lbStore_t;

