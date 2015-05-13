#include <Servo.h> 
#include <Thread.h>
#include <ThreadController.h>
 
Servo rightArmServo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
                
Servo leftArmServo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created  
                
  
ThreadController threadController = ThreadController();              
int rightArmPos = 0;    // variable to store the servo rightArmPosition 
int leftArmPos = 0;

Thread* rightArmThread = new Thread();
Thread* leftArmThread = new Thread();

void setup() 
{ 
  Serial.begin(9600);
  
  rightArmServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  leftArmServo.attach(10);
  
  rightArmThread->onRun(rightArmCallback);
  rightArmThread->setInterval(100);
  
  leftArmThread->onRun(leftArmCallback);
  leftArmThread->setInterval(100);
  
  threadController.add(rightArmThread);
  threadController.add(leftArmThread);
} 
 
void loop() 
{ 
  threadController.run();
}

void rightArmCallback() {
  moveArm(rightArmPos, rightArmServo, 5, 0, 60);
}

void leftArmCallback() {
  moveArm(leftArmPos, leftArmServo, 5, 90, 100);
}
 
void moveArm(int armPosition, Servo armServo, int delayMillis, int startPosition, int endPosition) {
  Serial.println("moveArm");
  for(armPosition = startPosition; armPosition < endPosition; armPosition += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
//    Serial.println("armPosition: " + armPosition);
    armServo.write(armPosition);              // tell servo to go to rightArmPosition in variable 'rightArmPos' 
    delay(delayMillis);                       // waits 15ms for the servo to reach the rightArmPosition 
  } 
  for(armPosition = endPosition; armPosition>=1; armPosition-=1)     // goes from 180 degrees to 0 degrees 
  {                                
//    Serial.println("armPosition: " + armPosition);
    armServo.write(armPosition);              // tell servo to go to rightArmPosition in variable 'rightArmPos' 
    delay(delayMillis);                       // waits 15ms for the servo to reach the rightArmPosition 
  }
}

