#include "PianoRoll.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>
#include "Musician.h"

File instructionFile;
Musician *musician;

void PianoRoll::init(Musician *initMusician) {
	pinMode(10, OUTPUT);
	SD.begin(4);
	musician = initMusician;
}

void PianoRoll::overrideBPM(int bpm) {
    Serial.print("Overriding BPM: ");
    Serial.println(bpm);
	overriddenBPM = bpm;
}

void PianoRoll::loadSong(String songName) {
	rightArmMovement = musician->getInitialState()[0];
	leftArmMovement = musician->getInitialState()[1];

	String songPathString = musician->getFolderName() + "/" + songName;
	char songPath[songPathString.length() + 1];
	songPathString.toCharArray(songPath, songPathString.length() + 1);

	Serial.println(songPath);
	if (SD.exists(songPath)) {
		Serial.println("Loading song " + songPathString);
		instructionFile = SD.open(songPath, FILE_READ);
		playingSong = true;
	} else {
		Serial.println("File " + songPathString + " not found!");
		playingSong = false;
	}
}

int PianoRoll::getValueFromString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length()-1;
    for(int i=0; i<=maxIndex && found<=index; i++){
        if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]).toInt() : 0;
}

int PianoRoll::getDelay() {
	return round(((.25 / loopBPM) * 60) * 1000);
}

unsigned char* PianoRoll::getStateSet() {

    if (instructionFile.available() != 0) {
        playingSong = true;

        parsedLine = instructionFile.readStringUntil('\n');

        if (overriddenBPM == 0) {
            loopBPM = getValueFromString(parsedLine, ',', 0);
        } else {
            loopBPM = overriddenBPM;
        }

        rightArmMovement = getValueFromString(parsedLine, ',', 1);

        leftArmMovement = getValueFromString(parsedLine, ',', 2);
        for (unsigned char i = 0; i <= 6; i++) {
            pixelColor[i] = getValueFromString(parsedLine, ',', i + 3);
        }

        parsedLine = "";

    } else if (playingSong && instructionFile.available() == 0) {
        overriddenBPM = 0;
        playingSong = false;
        Serial.println("Song finished");
        stop();
    }

	static unsigned char states[9];
	states[0] = rightArmMovement;
	states[1] = leftArmMovement;
    states[2] = pixelColor[0];
    states[3] = pixelColor[1];
    states[4] = pixelColor[2];
    states[5] = pixelColor[3];
    states[6] = pixelColor[4];
    states[7] = pixelColor[5];
    states[8] = pixelColor[6];

	return states;
}

void PianoRoll::stop() {
    overriddenBPM = 0;
	playingSong = false;
	Serial.println("PIANO ROLL STOPPED");
	instructionFile.close();

	rightArmMovement = musician->getFinalState()[0];
	leftArmMovement = musician->getFinalState()[1];

    pixelColor[0] = 0;
    pixelColor[1] = 0;
    pixelColor[2] = 0;
    pixelColor[3] = 0;
    pixelColor[4] = 0;
    pixelColor[5] = 0;
    pixelColor[6] = 0;
}
