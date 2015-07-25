#ifndef AXEMAN_H
#define AXEMAN_H

#include "Musician.h"
#include "Arduino.h"
#include <Servo.h>

class AxeMan: public Musician {
public:
	void setup();
	void powerOnSelfTest();
	void setState(String value1, String value2, String lightValue);
	String* getInitialState();
	String* getFinalState();
	String getFolderName();
private:
    int leftArmPos = 0;
    int rightArmPos = 0;
    Servo rightArmServo;
    Servo leftArmServo;

    // RIGHT ARM ROTATION OFFSET
    const int rotationOffset = 90;

    // LEFT ARM ARC
    const unsigned char leftArmArc = 90;

    // Rotation direction
    char direction = -1;
    unsigned char callsToSkip = 0;

    // PIN CONFIGURATION
    const unsigned char leftArmPin = 2;
    const unsigned char rightArmPin = 3;

    // ACTION LIST
    String restingState = "255";
    String sixteenthRest = "0";
    String quarterNote = "4";
    String eighthNote = "8";
    String sixteenthNote = "16";
};

#endif
