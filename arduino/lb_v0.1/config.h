/* File for main configuration */

// Pinout for send order to RPi to take a picture
// and recive the confirmation of picture taken
#define RPiCapturePin 12
#define RPiConfirmedPin 11

// Serial ports
#define xbeeSerial Serial1

// Activation time for sampling sensors
#define T_HOUR   14
#define T_MINUTE 00
#define T_SECOND 00

// AT codes
#define AT_Rejected 'R' // Rejected by Atomatic Mode
#define AT_Accepted 'A' // Accepted

// Servor motor control pinout
#define servoEnablePin 7
#define servoRightPin 9
#define servoLeftPin 8
#define servoRightStopOffset 128
#define servoLeftStopOffset 128

// Dc motor control pinout
#define dcEnablePin 3
#define dcRightPin 4
#define dcLeftPin 5
#define dcRightStopOffset 128
#define dcLeftStopOffset 128
