#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include "Adafruit_NeoPixel.h"

PianoRoll pianoRoll;
extern Musician *musician;
unsigned char* stateSet;

String serialAction = "";
String inputString = "";

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

void loop() {
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

	musician->setState(stateSet[0], stateSet[1]);

	delay(pianoRoll.getDelay());
}
