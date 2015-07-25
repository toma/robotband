#ifndef MUSICIAN_H
#define MUSICIAN_H

class Musician {
public:
	static Musician *makeMusician();

	virtual void powerOnSelfTest();
	virtual String getFolderName();
	virtual void setup();
	virtual void setState(String value1, String value2);
	virtual String* getInitialState();
	virtual String* getFinalState();
};

#endif
