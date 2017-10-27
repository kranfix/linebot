#include "config.h"

/* Servo motor functions */

// Pinout setup
void ServoSetup();

void ServoStop();

// Level: the level over or below the
// stop offset to set a forward or
// backward movement
void ServoMove(char level);


/* DC motor function */

// Pinout setup
void DcSetup();

void DcStop();

// Level: the level over or below the
// stop offset to set a forward or
// backward movement
void DcMove(char level);
