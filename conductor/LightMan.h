#include "Musician.h"

class LightMan : public Musician {
  public:
    void setup();
    void setState(unsigned char state[2]);
};