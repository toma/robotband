#ifndef MUSICIAN_H
#define MUSICIAN_H

class Musician {
public:
	static Musician *makeMusician();

	virtual void powerOnSelfTest();
	virtual String getFolderName();
	virtual void setup();
	virtual void setState(unsigned char value1, unsigned char value2);
	virtual unsigned char* getInitialState();
	virtual unsigned char* getFinalState();
};

#endif
