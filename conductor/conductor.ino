#include "PianoRoll.h"
#include "LightMan.h"

PianoRoll pianoRoll;
LightMan musician;
unsigned char states[] = {0,1};

void setup() 
{
  // String musicianName = pianoRoll.getMusician();
  // if (musicianName == MusicianNames.LIGHT_MAN) {
    musician.setup();
  // }
} 
 
void loop() 
{ 
  //fuck you C++
  if (states[0] == 0){
    states[0] = 1;
    states[1] = 0;
  } else {
    states[0] = 0;
    states[1] = 1;
  }

  // unsigned char = pianoRoll.getStateSet();
  musician.setState(states);
  delay(pianoRoll.getDelay());
  // pianoRoll.nextLine();
}
