#ifndef DRUMMER_H_
#define DRUMMER_H_

#include "Musician.h"
#include <Arduino.h>
#include <Servo.h>

class Drummer: public Musician {
public:
    Drummer();
	void setup();
	void powerOnSelfTest();
	void setState(String value1, String value2);
	String* getInitialState();
	String* getFinalState();
    String getFolderName();

private:
    int leftArmPos = 0;
    int rightArmPos = 0;
    Servo rightArmServo;
    Servo leftArmServo;

};

#endif /* DRUMMER_H_ */
