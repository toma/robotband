#include <Arduino.h>
// #include <Servo.h> // Where can I get this library from?
#include "AxeMan.h"

// // PIN CONFIGURATION
const unsigned char leftArmPin = 9;
const unsigned char rightArmPin = 10;

// // ACTION KEY
const unsigned char leftArmKey = 0;
const unsigned char rightArmKey = 1;

// SERVO CONFIGURATION
// a maximum of eight servo objects can be created 
// Servo rightArmServo;
// Servo leftArmServo;

// Arm positions
int leftArmPos = 0;
int rightArmPos = 0;


void AxeMan::setup() 
{ 
  // leftArmServo.attach(leftArmPin);
  // rightArmServo.attach(rightArmPin);
} 
 
void AxeMan::setState(unsigned char state[2]) 
{ 
}

// void rightArmCallback() {
//   moveArm(rightArmPos, rightArmServo, 3, 0, 20);
// }

// void leftArmCallback() {
//   leftArmServo.write(0.);
// }
 
// void moveArm(int armPosition, Servo armServo, int delayMillis, int startPosition, int endPosition) {
//   Serial.println("moveArm");
//   for(armPosition = startPosition; armPosition < endPosition; armPosition += 1)  // goes from 0 degrees to 180 degrees 
//   {                                  // in steps of 1 degree 
// //    Serial.println("armPosition: " + armPosition);
//     armServo.write(armPosition);              // tell servo to go to rightArmPosition in variable 'rightArmPos' 
//     delay(delayMillis);                       // waits 15ms for the servo to reach the rightArmPosition 
//   } 
//   for(armPosition = endPosition; armPosition>=1; armPosition-=1)     // goes from 180 degrees to 0 degrees 
//   {                                
// //    Serial.println("armPosition: " + armPosition);
//     armServo.write(armPosition);              // tell servo to go to rightArmPosition in variable 'rightArmPos' 
//     delay(delayMillis);                       // waits 15ms for the servo to reach the rightArmPosition 
//   }
// }
