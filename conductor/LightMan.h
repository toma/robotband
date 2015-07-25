#ifndef LIGHTMAN_H
#define LIGHTMAN_H

#include "Musician.h"

class LightMan: public Musician {
public:
	void setup();
	void powerOnSelfTest();
	void setState(String value1, String value2);
	String* getInitialState();
	String* getFinalState();
	String getFolderName();
};

#endif
