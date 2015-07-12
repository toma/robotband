#ifndef MUSICIAN_H
#define MUSICIAN_H
#define ARDUINO_ARCH_AVR true
#include "Musician.h"
#include <Servo.h>
#endif

class AxeMan : public Musician {
  public:
    void setup();
    void setState(unsigned char state[2]);
};