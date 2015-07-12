#include "AxeMan.h"

// // PIN CONFIGURATION
const unsigned char leftArmPin = 2;
const unsigned char rightArmPin = 3;

// // ACTION KEY
const unsigned char leftArmKey = 0;
const unsigned char rightArmKey = 1;

// // ACTION LIST
const unsigned char restingState = 255;
const unsigned char sixteenthRest = 0;
const unsigned char quarterNote = 4;
const unsigned char eighthNote = 8;
const unsigned char sixteenthNote = 16;

// // RIGHT ARM ROTATION OFFSET
const int rotationOffset = 90;

// // LEFT ARM ARC
const unsigned char leftArmArc = 90;

// Rotation direction
char direction = -1;
unsigned char callsToSkip = 0;

// Arm positions
int leftArmPos = 0;
int rightArmPos = 0;

// Servo configuration
// a maximum of eight servo objects can be created 
Servo rightArmServo;
Servo leftArmServo;

void AxeMan::setup() 
{ 
  leftArmServo.attach(leftArmPin);
  rightArmServo.attach(rightArmPin);
}

void AxeMan::setState(unsigned char state[2]) 
{
  leftArmPos = (leftArmArc/24) * state[leftArmKey] + ((180-leftArmArc)/2);
  leftArmServo.write(leftArmPos);

  if (callsToSkip > 0) { 
    callsToSkip--;
    return;
  }

  // for a quarter note it needs to move one quarter of it's distance in one delay
  if (state[rightArmKey] == quarterNote) {
    direction = direction * -1;
    rightArmPos = (direction * 45) + rotationOffset;
    rightArmServo.write(rightArmPos);
    callsToSkip = 3;
  }
  // for an eighth note it needs to move half it's distance in one delay
  else if (state[rightArmKey] == eighthNote) {
    direction = direction * -1;
    rightArmPos = (direction * 30) + rotationOffset;
    rightArmServo.write(rightArmPos);
    callsToSkip = 1;
  }
  // for a sixteenth note it needs to move it's full distance in one delay
  else if (state[rightArmKey] == sixteenthNote) {
    direction = direction * -1;
    rightArmPos = (direction * 15) + rotationOffset;
    rightArmServo.write(rightArmPos);
    callsToSkip = 0;
  }
  // for a restingState motion it needs to move to the resting state in one delay
  else if (state[rightArmKey] == restingState) {
    rightArmPos = 45 + rotationOffset;
    rightArmServo.write(rightArmPos);
    direction = -1;
    callsToSkip = 0;
  }
  else if (state[rightArmKey] == sixteenthRest) {
    rightArmServo.write(rightArmPos);
    callsToSkip = 0;
  }
}
