#include "PianoRoll.h"

// Musician Types
const int LightMan = 0;
const int AxeMan = 1;
const int Drummer = 2;

// const unsigned char testRightArm[] = {255,255,255,255,16,0,0,16,0,0,16,0,0,0,0,0,0,16,0,16,0,0,16,0,16,0,0,0};
const unsigned char testRightArm[] = {255,255,255,255,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};

// Shred you litter little mother fucker
// const unsigned char testRightArm[] = {255,255,255,255,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16}; 

const unsigned char testLeftArm[] = {1,1,1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,21,22,23,24,24,24};
// const unsigned char testLeftArm[] = {7,7,7,7,7,7,9,9,7,7,7,7,5,5,9,9,7,7,7,7,7,5,5,7,7,7,7,7};

int currentPhrase = 0;

int PianoRoll::getMusicianType(){
  return AxeMan;
}

int PianoRoll::getDelay() {
  // delay = file.get_delay
  // At 60bpm 1 1/16th note is 125ms, this is our shortest strum
  // At 60bpm 1 1/4 note is 1s, this is our longest strum

  // int bpm = 60;
  // int delay = (1000 * bpm)/(60*8);
  // int delay = 100;
  int delay = 100;
  return delay;
}

unsigned char* PianoRoll::getStateSet() {
  static unsigned char states[2];
  states[0] = testLeftArm[currentPhrase];
  states[1] = testRightArm[currentPhrase];

  //  Generate some testing data for LightMan
  // if (currentPhrase % 2 == 0) {
  //   states[0] = 2;
  // } else {
  //   states[0] = 1;
  // }

  // if (currentPhrase % 2 == 1) {
  //   states[1] = 2;
  // } else {
  //   states[1] = 1;
  // }



  return states;
}

void PianoRoll::nextLine() {
  if (currentPhrase == 28) {
    currentPhrase = 0;
    return;
  }
  currentPhrase++;
}
