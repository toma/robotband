#include <Arduino.h>
#include "LightMan.h"

// PIN CONFIGURATION
const unsigned char leftLightPin = 9;
const unsigned char rightLightPin = 10;

// ACTION KEY
const unsigned char leftLightKey = 0;
const unsigned char rightLightKey = 1;

void LightMan::setup() {
	pinMode(leftLightPin, OUTPUT);
	pinMode(rightLightPin, OUTPUT);
}

void LightMan::powerOnSelfTest() {
}

void LightMan::setState(String leftLight, String rightLight, String lightValue) {
	if (leftLight.equals("1")) {
		digitalWrite(leftLightPin, HIGH);
	} else {
		digitalWrite(leftLightPin, LOW);
	}

	if (rightLight.equals("1")) {
		digitalWrite(rightLightPin, HIGH);
	} else {
		digitalWrite(rightLightPin, LOW);
	}
}

String * LightMan::getInitialState() {
	return new String { 0, 0 };
}

String * LightMan::getFinalState() {
	return new String { 0, 0 };
}

String LightMan::getFolderName() {
	return "LIGHTMAN";
}
