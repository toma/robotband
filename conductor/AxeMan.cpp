#include <Arduino.h>
#include <Servo.h> // Has to be included at top level?
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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  leftArmServo.attach(leftArmPin);
  rightArmServo.attach(rightArmPin);
}

void AxeMan::setState(unsigned char rightArmValue, unsigned char leftArmValue) {
  leftArmPos = (leftArmArc/24) * leftArmValue + ((180-leftArmArc)/2);
  Serial.print("Left arm pos: ");
  Serial.println(leftArmPos);
  leftArmServo.write(leftArmPos);

  if (callsToSkip > 0) { 
    callsToSkip--;
    return;
  }

  // for a quarter note it needs to move one quarter of it's distance in one delay
  if (rightArmValue == quarterNote) {
    direction = direction * -1;
    rightArmPos = (direction * 45) + rotationOffset;
    callsToSkip = 3;
  }
  // for an eighth note it needs to move half it's distance in one delay
  else if (rightArmValue == eighthNote) {
    direction = direction * -1;
    rightArmPos = (direction * 30) + rotationOffset;
    callsToSkip = 1;
  }
  // for a sixteenth note it needs to move it's full distance in one delay
  else if (rightArmValue== sixteenthNote) {
    direction = direction * -1;
    rightArmPos = (direction * 15) + rotationOffset;
    callsToSkip = 0;
  }
  // for a restingState motion it needs to move to the resting state in one delay
  else if (rightArmValue == restingState) {
    rightArmPos = 45 + rotationOffset;
    direction = -1;
    callsToSkip = 0;
  }
  else if (rightArmValue == sixteenthRest) {
    callsToSkip = 0;
  }

  Serial.print("right arm pos: ");
  Serial.println(rightArmPos);
  rightArmServo.write(rightArmPos);  
}

