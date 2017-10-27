#include "config.h"
#include "movements.h"
//#include "timemanager.h"

//time_ now;

//uint8_t Nsch = 1; // number of scheduled work times
/*time_t schedule[Nsch] = {
  {T_HOUR,T_MINUTE,T_SECOND}
};*/
//bool worked[Nsch];

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  //time_setup();
  ServoSetup();
  pinMode(RPiCapturePin,OUTPUT);

  // looking for pending scheduled works
  //time_read(&now);
  /*for(uint8_t i = 0; i < Nsch; i++){
    worked[i] = true;
    if(now.h < workScheduled.h) {
      worked[i] = false;
    } else if (now.m < workScheduled.m) {
      worked[i] = false;
    } else if (now.s < workScheduled.s) {
      worked[i] = false;
    }
  }*/
}

void loop(){
  //time_red(&now);

  /*for (uint8_t i = 0; i < Nsch && !worked[i]; i++) {
    if (now.h >= workScheduled.h &&
        now.m >= workScheduled.m &&
        now.s >= workScheduled.s) {
      linebotProcess();
      worked[i] = true;
    }
  }*/

  if(xbeeSerial.available() > 0){
    char in = xbeeSerial.read();
    switch(in){
      case 'F': // Forward
        ServoMove(50);
        Serial.println("Moving Forward");
        xbeeSerial.write('A');
        break;

      case 'B': // Backward
        ServoMove(-50);
        Serial.println("Moving Backward");
        xbeeSerial.write('A');
        break;

      case 'S': // Stop
        ServoStop();
        Serial.println("Stop");
        xbeeSerial.write('A');
        break;
        
      case 'C': // Stop
        digitalWrite(RPiCapturePin,HIGH);
        delay(500);
        Serial.println("Capturing");
        xbeeSerial.write('A');
        digitalWrite(RPiCapturePin,LOW);
        break;
    }
  }
}

void linebotProcess() {

}
