#include <Arduino.h>

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

// Setting EEPROM memory
//#define CLEAREEPROM

// EEPROM
#define RtcSetDir 0

// Arduino 5V pin real voltage
#define V5 4.6

// Attachable Pin: 2 and 3 in Arduino Nano
#define wakeRtcPin      2     // pin used for waking up
#define wakeOnRtc       LOW

#define wakeButtonPin   3     // pin used for waking up
#define wakeOnButton    LOW
