#ifndef LIGHTMAN_H
#define LIGHTMAN_H

#include "Musician.h"

class LightMan: public Musician {
public:
	void setup();
	void setState(unsigned char value1, unsigned char value2);
	unsigned char* getInitialState();
	unsigned char* getFinalState();
	String getFolderName();
};

#endif
