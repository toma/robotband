#include <Arduino.h>
#include <Servo.h> // Has to be included at top level?
#include "AxeMan.h"

void AxeMan::setup() {
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);

	leftArmServo.attach(leftArmPin);
	rightArmServo.attach(rightArmPin);
}

void AxeMan::powerOnSelfTest() {
    //Move arms through each extreme
    rightArmServo.write(180);
    leftArmServo.write(180);
    delay(1000);
    rightArmServo.write(0);
    leftArmServo.write(0);
}

void AxeMan::setState(String rightArmValue, String leftArmValue, String lightValue) {
	leftArmPos = (leftArmArc / 24) * leftArmValue.toInt() + ((180 - leftArmArc) / 2);
//  Serial.print("Left arm pos: ");
//  Serial.println(leftArmPos);
	leftArmServo.write(leftArmPos);

	//lights.setLights(lightValue)

    /*
     * light::SetLights(String lightString) {
     *     //parse string
     *     //set values for each light
     * }
     */

	if (callsToSkip > 0) {
		callsToSkip--;
		return;
	}

	// for a quarter note it needs to move one quarter of it's distance in one delay
	if (rightArmValue.equals(quarterNote)) {
		direction = direction * -1;
		rightArmPos = (direction * 45) + rotationOffset;
		callsToSkip = 3;
	}
	// for an eighth note it needs to move half it's distance in one delay
	else if (rightArmValue.equals(eighthNote)) {
		direction = direction * -1;
		rightArmPos = (direction * 30) + rotationOffset;
		callsToSkip = 1;
	}
	// for a sixteenth note it needs to move it's full distance in one delay
	else if (rightArmValue.equals(sixteenthNote)) {
		direction = direction * -1;
		rightArmPos = (direction * 15) + rotationOffset;
		callsToSkip = 0;
	}
	// for a restingState motion it needs to move to the resting state in one delay
	else if (rightArmValue == restingState) {
		rightArmPos = 45 + rotationOffset;
		direction = -1;
		callsToSkip = 0;
	} else if (rightArmValue.equals(sixteenthRest)) {
		callsToSkip = 0;
	}

//  Serial.print("right arm pos: ");
//  Serial.println(rightArmPos);
	rightArmServo.write(rightArmPos);
}

String * AxeMan::getInitialState() {
	return new String { 255, 7 };
}

String * AxeMan::getFinalState() {
	return new String { 255, 1 };
}

String AxeMan::getFolderName() {
	return "AXEMAN";
}
