#include "PianoRoll.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>
#include "Musician.h"

// Musician Types
const unsigned char DEFAULT_RIGHT_ARM_MOVEMENT = 255;
const unsigned char DEFAULT_LEFT_ARM_MOVEMENT = 7;
const int Unknown = -1;
const int LightMan = 0;
const int AxeMan = 1;
const int Drummer = 2;

int loopBPM = 100;
unsigned char rightArmMovement = DEFAULT_RIGHT_ARM_MOVEMENT;
unsigned char leftArmMovement = DEFAULT_LEFT_ARM_MOVEMENT;

char inputChar;
String parsedBPM;
String parsedRightArm;
String parsedLeftArm;
unsigned char index = 0;

bool hasMoreRows = true;

File instructionFile;

Musician *musician;

void PianoRoll::init(Musician *initMusician) {
  pinMode(10, OUTPUT);
  SD.begin(4);
  musician = initMusician;
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
  } else {
    Serial.println("File " + songPathString + " not found!");
  }
}

void PianoRoll::readLine() {

  if (instructionFile.available() != 0) {
    inputChar = instructionFile.peek();
    while (inputChar != '\n') {
      inputChar = instructionFile.read();

      if (index == 0 && inputChar != ',') {
        parsedBPM += (String) inputChar;
      } else if (index == 1 && inputChar != ',') {
        parsedRightArm += (String) inputChar;
      } else if (index == 2 && inputChar != ',') {
        parsedLeftArm += (String) inputChar;
      }

      if (inputChar == ',') {
        index++;
      }
    }

    index = 0;

    loopBPM = parsedBPM.toInt();
    rightArmMovement = parsedRightArm.toInt();
    leftArmMovement = parsedLeftArm.toInt();

    parsedBPM = "";
    parsedRightArm = "";
    parsedLeftArm = "";
  }
  else {
//    Serial.println("Song finished");
    stop();
  }
}

bool PianoRoll::hasRows() {
  return hasMoreRows;
}

int PianoRoll::getDelay() {
  return round(((.25 / loopBPM) * 60) * 1000);
}

unsigned char* PianoRoll::getStateSet() {
  static unsigned char states[2];
  states[0] = rightArmMovement;
  states[1] = leftArmMovement;

  return states;
}

void PianoRoll::stop() {
//  Serial.println("PIANO ROLL STOPPED");
	  instructionFile.close();

	rightArmMovement = musician->getFinalState()[0];
	leftArmMovement = musician->getFinalState()[1];
}
