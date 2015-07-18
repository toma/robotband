// A state is the position of an action
// A state set is the series of states for a musician
// An instruction set is the ordered series of state sets and corresponding
//     delays for the entire performance

#ifndef PIANOROLL_H
#define PIANOROLL_H

#include "Arduino.h"
#include "Musician.h"

class PianoRoll {
  public: 
    void init(Musician *musician);
    void loadSong(String songName);
    int getDelay();
    unsigned char* getStateSet();
    void readLine();
    bool hasRows();
    void stop();
};

#endif
