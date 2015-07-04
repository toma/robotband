#include "PianoRoll.h"
#include "Musician.h"

PianoRoll pianoRoll;
Musician* musician;

void setup() 
{
  int musicianType = pianoRoll.getMusicianType();
  musician = Musician::makeMusician(musicianType);
  musician->setup();
} 
 
void loop()
{ 
  unsigned char* stateSet = pianoRoll.getStateSet();
  musician->setState(stateSet);
  delete[] stateSet;
  delay(pianoRoll.getDelay());
  pianoRoll.nextLine();
}
