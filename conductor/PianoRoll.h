#ifndef PIANOROLL_H
#define PIANOROLL_H

#include "Arduino.h"
#include "Musician.h"

class PianoRoll {
public:
	void init(Musician *musician);
	void loadSong(String songName);
	int getDelay();
	unsigned char* getStateSet();
	void stop();
	void overrideBPM(int bpm);
private:
    int overriddenBPM = 0;
    unsigned char index = 0;
    String parsedLine;
    char inputChar;
    int loopBPM = 100;
    unsigned char rightArmMovement;
    unsigned char leftArmMovement;
    bool playingSong = false;
    unsigned char pixelColor[7];
    int getValueFromString(String data, char separator, int index);
};

#endif
