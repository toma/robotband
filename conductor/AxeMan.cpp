#include <Arduino.h>
#include <Servo.h> // Has to be included at top level?
#include "AxeMan.h"

// // PIN CONFIGURATION
const unsigned char leftArmPin = 9;
const unsigned char rightArmPin = 10;

// // ACTION KEY
const unsigned char leftArmKey = 0;
const unsigned char rightArmKey = 1;

// // ACTION LIST
const unsigned char restingState = 255;
const unsigned char sixteenthRest = 0;
const unsigned char quarterNote = 4;
const unsigned char eighthNote = 8;
const unsigned char sixteenthNote = 16;

// // ROTATION OFFSET
const int rotationOffset = 90;

// Rotation direction
unsigned char direction = -1;

unsigned char callsToSkip = 0;

unsigned char position = 0;

// SERVO CONFIGURATION
// a maximum of eight servo objects can be created 
Servo rightArmServo;
Servo leftArmServo;

// Arm positions
int leftArmPos = 0;
int rightArmPos = 0;

void AxeMan::setup() 
{ 
  leftArmServo.attach(leftArmPin);
  rightArmServo.attach(rightArmPin);
}

void AxeMan::setState(unsigned char state[2]) 
{
  if (callsToSkip > 0) { 
    callsToSkip--;
    return;
  }

  // for a quarter note it needs to move one quarter of it's distance in one delay
  if (state[rightArmKey] == quarterNote) {
    direction = direction * -1;
    position = (direction * 60) + rotationOffset;
    rightArmServo.write(position);
    callsToSkip = 3;
  }
  // for an eighth note it needs to move half it's distance in one delay
  else if (state[rightArmKey] == eighthNote) {
    direction = direction * -1;
    position = (direction * 40) + rotationOffset;
    rightArmServo.write(position);
    callsToSkip = 1;
  }
  // for a sixteenth note it needs to move it's full distance in one delay
  else if (state[rightArmKey] == sixteenthNote) {
    direction = direction * -1;
    position = (direction * 20) + rotationOffset;
    rightArmServo.write(position);
    callsToSkip = 0;
  }
  // for a restingState motion it needs to move to the resting state in one delay
  else if (state[rightArmKey] == restingState) {
    direction = 1;
    position = 60 + rotationOffset;
    rightArmServo.write(position);
    callsToSkip = 0;
  }
  else if (state[rightArmKey] == sixteenthRest) {
    rightArmServo.write(position);
    callsToSkip = 0;
  }
}
