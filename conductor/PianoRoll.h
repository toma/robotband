#ifndef PIANOROLL_H
#define PIANOROLL_H

#include "Arduino.h"
#include "Musician.h"

class PianoRoll {
public:
	void init(Musician *musician);
	void loadSong(String songName);
	int getDelay();
	String* getStateSet();
	void readLine();
	void stop();
	void overrideBPM(int bpm);
private:
    int overriddenBPM = 0;
    unsigned char index = 0;
    String parsedBPM;
    String parsedRightArm;
    String parsedLeftArm;
    String parsedRestOfCommand;
    char inputChar;
    int loopBPM = 100;
    String rightArmMovement;
    String leftArmMovement;
    bool playingSong = false;
};

#endif
