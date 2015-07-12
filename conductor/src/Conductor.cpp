#include "Arduino.h"
#include "Conductor.h"
#define ARDUINO_ARCH_AVR true

#include "PianoRoll.h"
#include "Musician.h"
#include <Servo.h>

PianoRoll pianoRoll;
Musician* musician;

void setup()
{
    Serial.begin(9600); // For debugging
    int musicianType = pianoRoll.getMusicianType();
    musician = Musician::makeMusician(musicianType);
    musician->setup();
}

void loop()
{
//    unsigned char* stateSet = pianoRoll.getStateSet();
//    musician->setState(stateSet);
//    delete[] stateSet;
//    delay(pianoRoll.getDelay());
//    pianoRoll.nextLine();
}

