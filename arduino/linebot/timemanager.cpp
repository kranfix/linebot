#include "config.h"
#include <Wire.h>
/*#include "RTClib.h"

RTC_DS3231 RTC;
DateTime now;

void time_setup(){
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
}

void time_read(time_t *t){
  now = RTC.now();
  t->h = (now.hour(),DEC);
  t->m = (now.minute(),DEC);
  t->s = (now.second(),DEC);
}*/
