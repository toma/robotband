#include "PianoRoll.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <math.h>

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

String musicianName = "";

bool hasMoreRows = true;

File instructionFile;
//TODO: Eventually we need to read from setlist.csv to get the order of songs to play

void PianoRoll::initSD() {
  pinMode(10, OUTPUT);
  SD.begin(4);
}

void PianoRoll::loadSong(String songName) {
  //Use 5, 6 and 7 to determine binary value of musician, 5V into the pin means it's on

  //TODO: Needs to happen elsewhere
  String songPathString = musicianName + "/" + songName;
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

int PianoRoll::getMusicianType() {
  unsigned char pin5Value = digitalRead(5);
  unsigned char pin6Value = digitalRead(6);
  unsigned char pin7Value = digitalRead(7);

  unsigned char bitValue = pin5Value + (pin6Value * 2) + (pin7Value * 4);

  Serial.print("Bit Value: ");
  Serial.println(bitValue);

  switch (bitValue) {
    case 0:
      musicianName = "LIGHTMAN";
      return LightMan;
      break;
    case 1:
      musicianName = "AXEMAN";
      return AxeMan;
      break;
    case 2:
      musicianName = "DRUMMER";
      return Drummer;
      break;
    default:
      musicianName = "UNKNOWN";
      return Unknown;
      break;
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
    Serial.println("Song finished");
    stop();
//    //TODO: Stop moving
//    hasMoreRows = false;
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
  Serial.println("STOPPING PIANO ROLL");
  instructionFile.close();
  rightArmMovement = DEFAULT_RIGHT_ARM_MOVEMENT;
  leftArmMovement = DEFAULT_LEFT_ARM_MOVEMENT;}
