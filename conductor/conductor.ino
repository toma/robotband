#include "PianoRoll.h"
#include "Musician.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

PianoRoll pianoRoll;
Musician* musician;
unsigned char* stateSet;

String serialAction = "";
String inputString = "";

void setup() 
{
  Serial.begin(9600); // For debugging

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  int musicianType = pianoRoll.getMusicianType();
  musician = Musician::makeMusician(musicianType);
  musician->setup();

  pianoRoll.initSD();

} 

void loop()
{ 
    if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("READ STRING: ");
        Serial.println(inputString);
        if (inputString == "STOP") {
            pianoRoll.stop();
    	} else {
       	    pianoRoll.loadSong(inputString);
        }
    } 
//	if (pianoRoll.hasRows()) {
		pianoRoll.readLine();
		stateSet = pianoRoll.getStateSet();
		int loopDelay = pianoRoll.getDelay();

		Serial.print("Delay: ");
		Serial.println(loopDelay);
		Serial.print("Right Arm: ");
		Serial.println(stateSet[0]);
		Serial.print("Left Arm: ");
		Serial.println(stateSet[1]);
		musician->setState(stateSet[0], stateSet[1]);

		delay(pianoRoll.getDelay());
//	}
}
