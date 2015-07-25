#include <Arduino.h>
#include "Drummer.h"
#include <Servo.h> // Has to be included at top level?

// // PIN CONFIGURATION
const unsigned char leftArmPin = 2;
const unsigned char rightArmPin = 3;

const unsigned char leftArmArc = 90;
const unsigned char rightArmArc = 90;

// Arm positions
//int leftArmPos = 0;
//int rightArmPos = 0;

//Servo rightArmServo;
//Servo leftArmServo;

Drummer::Drummer() {

}

void Drummer::setup() {
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);

	leftArmServo.attach(leftArmPin);
	rightArmServo.attach(rightArmPin);
}

void Drummer::powerOnSelfTest() {
    //Move arms through each extreme
    rightArmServo.write(180);
    leftArmServo.write(180);
    delay(1000);
    rightArmServo.write(0);
    leftArmServo.write(0);
}

void Drummer::setState(String rightArmValue, String leftArmValue) {

    leftArmPos = (leftArmArc / 24) * leftArmValue.toInt() + ((180 - leftArmArc) / 2);
    leftArmServo.write(leftArmPos);

    rightArmPos = (rightArmArc / 24) * rightArmValue.toInt() + ((180 - rightArmArc) / 2);
    rightArmServo.write(rightArmPos);

}

String* Drummer::getInitialState() {
	return new String { 15, 15 };
}

String* Drummer::getFinalState() {
	return new String { 1, 1 };
}

String Drummer::getFolderName() {
	return "DRUMMER";
}
