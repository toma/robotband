#ifndef MUSICIAN_H
#define MUSICIAN_H
#include "Musician.h"
#endif

class LightMan : public Musician {
  public:
    void setup();
    void setState(unsigned char state[]);
    void setState2(unsigned char value1, unsigned char value2);
};
