#ifndef AXEMAN_H
#define AXEMAN_H

#include "Musician.h"
#include "Arduino.h"
#include <Servo.h>

class AxeMan: public Musician {
public:
	void setup();
	void powerOnSelfTest();
	void setState(unsigned char value1, unsigned char value2);
	unsigned char* getInitialState();
	unsigned char* getFinalState();
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
    const unsigned char restingState = 255;
    const unsigned char sixteenthRest = 0;
    const unsigned char quarterNote = 4;
    const unsigned char eighthNote = 8;
    const unsigned char sixteenthNote = 16;
};

#endif
