#include "PianoRoll.h"
#include "Musician.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

PianoRoll pianoRoll;
Musician* musician;
unsigned char* stateSet;

void setup() 
{
  Serial.begin(9600); // For debugging

  pianoRoll.initSD();
    
  int musicianType = pianoRoll.getMusicianType();
  musician = Musician::makeMusician(musicianType);
  musician->setup();
} 
 
void loop()
{ 
  if (pianoRoll.hasRows()) {
    pianoRoll.readLine();
    stateSet = pianoRoll.getStateSet();
    int loopDelay = pianoRoll.getDelay();
  
    Serial.print("Delay: ");
    Serial.println(loopDelay);
    Serial.print("Right Arm: ");
    Serial.println(stateSet[0]);
    Serial.print("Left Arm: ");
    Serial.println(stateSet[1]);
//    musician->setState(stateSet);
    musician->setState2(stateSet[0], stateSet[1]);
    
    delay(pianoRoll.getDelay());
  }
}
