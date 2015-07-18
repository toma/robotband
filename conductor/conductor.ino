#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

PianoRoll pianoRoll;
extern Musician *musician;
unsigned char* stateSet;

String serialAction = "";
String inputString = "";

void setup()
{
  Serial.begin(9600); // For debugging

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

//  int musicianType = pianoRoll.getMusicianType();
  musician = Musician::makeMusician();
  musician->setup();

  pianoRoll.init(musician);

}


//:TODO:
// Create drummer
// Create HSF.csv for each musician that loops something decent for non-scripted songs
//
void loop()
{
    if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        Serial.print("READ STRING FROM SERIAL: ");
        Serial.println(inputString);
        if (inputString.equalsIgnoreCase("STOP")) {
            pianoRoll.stop();
    	} else if (inputString.equalsIgnoreCase("WHOAMI")) {
    		Serial.println(musician->getFolderName());
    	} else {
       	    pianoRoll.loadSong(inputString);
        }
    }
		pianoRoll.readLine();
		stateSet = pianoRoll.getStateSet();
		int loopDelay = pianoRoll.getDelay();

//		Serial.print("Delay: ");
//		Serial.println(loopDelay);
//		Serial.print("Right Arm: ");
//		Serial.println(stateSet[0]);
//		Serial.print("Left Arm: ");
//		Serial.println(stateSet[1]);
		musician->setState(stateSet[0], stateSet[1]);

		delay(pianoRoll.getDelay());
}
