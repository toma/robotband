#include "PianoRoll.h"
#include <Arduino.h>

int currentPhrase = 0;

int PianoRoll::getDelay() {
  // delay = file.get_delay
  int delay = 500;
  return delay;
}

unsigned char* PianoRoll::getStateSet() {
  static unsigned char states[2]; // = {0,0};

  //  Generate some testing data
  if (currentPhrase % 2 == 0) {
    states[0] = 0;
  } else {
    states[0] = 1;
  }

  if (currentPhrase % 2 == 1) {
    states[1] = 0;
  } else {
    states[1] = 1;
  }

  return states;
}

void PianoRoll::nextLine() {
  currentPhrase++;
}