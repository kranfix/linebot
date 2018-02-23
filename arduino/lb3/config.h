#include <Arduino.h>

// ID
#define ID 1

// Line maximun meter
#define LineMeterLong 700.0 // cm

/*************  Infrared Sensors ************/
#define IrForward        A1 //A0
#define IrBackward       A2 //A1
#define IrDetectionLevel  410

/************ Ultrasonic sensor *************/
#define Trigger 6
#define Echo    5 //7

/************** Encoder-Motor ***************/
// Motor
#define MotorForward      9 //11
#define MotorBackward    10 //12

// Encoder
#define EncoderPin    4   //8
#define Diameter      1.4 // cm
#define Slots        40
#define Distance    200   // cm
/************ Devices Activator *************/
#define activatorPin LED_BUILTIN
/********************************************/
// Setting EEPROM memory
//#define CLEAREEPROM

// Frecuencia de wake-up
//#define wakeUpFreq 0x8 // Every Day (24 hours)
#define wakeUpFreq 0xC // Every Hour
//#define wakeUpFreq 0xE // Every Minute
//define wakeUpFreq 0xF // Every Secong

// Arduino 5V pin real voltage
#define V5 4.6

// Attachable Pin: 2 and 3 in Arduino Nano
#define wakeRtcPin      2     // pin used for waking up
#define wakeOnRtc       LOW

#define wakeButtonPin   3     // pin used for waking up
#define wakeOnButton    LOW

// Battery pin
#define batPin    A0
#define batLevel1  900 // 0-1023
#define batLevel2  930 // 0-1023

/********* Defulat LineBot Task List ********/
#define defaultLbTask cuyRutine
#define NumOfTask 6
