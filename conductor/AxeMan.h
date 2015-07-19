#ifndef AXEMAN_H
#define AXEMAN_H

#include "Musician.h"
#include "Arduino.h"

class AxeMan: public Musician {
public:
	void setup();
	void powerOnSelfTest();
	void setState(unsigned char value1, unsigned char value2);
	unsigned char* getInitialState();
	unsigned char* getFinalState();
	String getFolderName();
};

#endif
