#include "PianoRoll.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

// Musician Types
const int Unknown = -1;
const int LightMan = 0;
const int AxeMan = 1;
const int Drummer = 2;

int loopBPM = 100;
unsigned char rightArmMovement = 255;
unsigned char leftArmMovement = 7;

char inputChar;
String parsedBPM;
String parsedRightArm;
String parsedLeftArm;
unsigned char index = 0;

bool hasMoreRows = true;

File instructionFile;
//TODO: Eventually we need to read from setlist.csv to get the order of songs to play

void PianoRoll::initSD() {
  pinMode(10, OUTPUT);
  SD.begin(4);

  //TODO: Needs to happen elsewhere
  if (SD.exists("SONG1.CSV")) {
    Serial.println("Loading song SONG1.CSV");
    instructionFile = SD.open("SONG1.CSV", FILE_READ);
  } else {
    Serial.println("File SONG1.CSV not found!");
  }
}

int PianoRoll::getMusicianType(){
  
  //Read from musician.csv
  if (SD.exists("MUSICIAN.CSV")) {
    File musicianFile = SD.open("MUSICIAN.CSV", FILE_READ);
    String musicianName = musicianFile.readStringUntil('\n');
    Serial.println("Initializing Musician: " + musicianName);
    if (musicianName.equals("AxeMan")) {
      return AxeMan;  
    } else if (musicianName.equals("LightMan")) {
      return LightMan;
    } else if (musicianName.equals("Drummer")) {
      return Drummer;
    } else {
      return Unknown;
    }
    musicianFile.close();
  } else {
    Serial.println("File MUSICIAN.CSV not found!");
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
  } else {
    Serial.println("Song finished");
    //TODO: Stop moving
    hasMoreRows = false;
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
