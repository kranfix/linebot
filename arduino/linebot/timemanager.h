#include "config.h"

struct time_t {
  uint8_t h; // hour
  uint8_t m; // minutes
  uint8_t s; // seconds
};

void time_setup();
void time_read(time_t *hms);
  
