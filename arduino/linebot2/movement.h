/*
Author: Frank Moreno
*/

#define MOVE_STOP     0
#define MOVE_FORWARD  1
#define MOVE_BACKWARD 2

/*
_F: Motor Forward Pin
_B: Motor Backward Pin
_f: IR sensor Forward Pin
_b: IR sensor Backward Pin
*/
void moveSetup(int _F, int _B, int _f, int _b, int detectionLevel);

// Movments
void moveForward();
void moveBackward();
void moveStop();

// Usable in loop functions
void moveSet(int _status);
void moveLoop();
