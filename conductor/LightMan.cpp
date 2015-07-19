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

void LightMan::setState(unsigned char leftLight, unsigned char rightLight) {
	if (leftLight == 1) {
		digitalWrite(leftLightPin, HIGH);
	} else {
		digitalWrite(leftLightPin, LOW);
	}

	if (rightLight == 1) {
		digitalWrite(rightLightPin, HIGH);
	} else {
		digitalWrite(rightLightPin, LOW);
	}
}

unsigned char * LightMan::getInitialState() {
	return new unsigned char[2] { 0, 0 };
}

unsigned char * LightMan::getFinalState() {
	return new unsigned char[2] { 0, 0 };
}

String LightMan::getFolderName() {
	return "LIGHTMAN";
}
