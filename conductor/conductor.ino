#include "PianoRoll.h"
#include "LightMan.h"

PianoRoll pianoRoll;
LightMan musician;

void setup() 
{
  // String musicianName = pianoRoll.getMusician();
  // if (musicianName == MusicianNames.LIGHT_MAN) {
    musician.setup();
  // }
} 
 
void loop() 
{ 
  unsigned char* stateSet = pianoRoll.getStateSet();
  musician.setState(stateSet);
  delete[] stateSet;
  delay(pianoRoll.getDelay());
  pianoRoll.nextLine();
}
