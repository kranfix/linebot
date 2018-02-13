#include <Arduino.h>

// Setting EEPROM memory
//#define CLEAREEPROM

// Movement
#define MotorForward      9 //11
#define MotorBackward    10 //12
#define IrForward        A1 //A0
#define IrBackward       A2 //A1
#define DetectionLevel  410

// Ultrasonic sensor
#define Trigger 6
#define Echo    5 //7

// Encoder
#define Encoder  4 //8
#define Diameter 1.4 // cm
#define Slots    40
#define Distance 200 // cm
//#define Distance 400 // cm

// MQ2 - CO2
#define Mq2 A0 //A2
