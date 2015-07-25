#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

PianoRoll pianoRoll;
extern Musician *musician;
String* stateSet;

String serialAction = "";
String inputString = "";

bool enteredLoop = false;

void setup() {
	Serial.begin(9600); // For debugging

	pinMode(5, INPUT);
	pinMode(6, INPUT);
	pinMode(7, INPUT);

	musician = Musician::makeMusician();
	musician->setup();

    musician->powerOnSelfTest();

	pianoRoll.init(musician);
}

//:TODO:
// Create HSF.csv for each musician that loops something decent for non-scripted songs
//
void loop() {
    if (!enteredLoop) {
        Serial.println("LOOP_START");
        enteredLoop = true;
    }

	if (Serial.available() > 0) {
		inputString = Serial.readStringUntil('\n');
		if (inputString.equalsIgnoreCase("STOP")) {
			pianoRoll.stop();
		} else if (inputString.equalsIgnoreCase("WHOAMI")) {
            Serial.println(musician->getFolderName());
        } else if (inputString.substring(0, 3).equals("HSF")) {
            //Set BPM in piano roll from HSFXX, where XXX is the BPM and play HSF.CSV
            Serial.println("HSF!");
            Serial.print("BPM: ");
            String bpm = inputString.substring(3, inputString.length());
            pianoRoll.overrideBPM(bpm.toInt());
            pianoRoll.loadSong("HSF.CSV");
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
