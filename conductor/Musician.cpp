#include "LightMan.h"

Musician *Musician::makeMusician(int musicianType)
{
  if (musicianType == 0) {
    return new LightMan;
  }
}