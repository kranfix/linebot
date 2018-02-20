#include "linebot.h"
#include "config.h"

//-----------------------------------------------------------------------------------
lbTask_t justSleep[1] = {
  {Action::Stop,           0, true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t FTE[1] = { // Forward  with Tope    (high priority) and Encoder (low priority)
  {Action::Forward, LineMeterLong*2, true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t FET[1] = { // Forward  with Encoder (high priority) and Tope    (low priority)
  {Action::Forward, LineMeterLong, false, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t BTE[1] = { // Backward with Tope    (high priority) and Encoder (low priority)
  {Action::Backward, -LineMeterLong, true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t BET[1] = { // Backward with Encoder (high priority) and Tope    (low priority)
  {Action::Backward, 0, false, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t simpleAutomatic[2] = {
  {Action::Forward,  LineMeterLong, true, lbTrans::Nop  },
  {Action::Backward,             0, true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t sleepAutomatic[2] = {
  {Action::Forward,  LineMeterLong, true, lbTrans::Sleep},
  {Action::Backward,             0, true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t simpleMiddleAutomatic[2] = {
  {Action::Forward,  LineMeterLong/2, false, lbTrans::Nop  },
  {Action::Backward,               0,  true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
lbTask_t sleepMiddleAutomatic[2] = {
  {Action::Forward, LineMeterLong/2, false, lbTrans::Sleep},
  {Action::Backward,              0,  true, lbTrans::Sleep}
};
//-----------------------------------------------------------------------------------
