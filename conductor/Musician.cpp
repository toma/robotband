#include "LightMan.h"
#include "AxeMan.h"

Musician *Musician::makeMusician(int musicianType)
{
  switch ( musicianType )
      {
         case 0:
            return new LightMan;
            break;
         case 1:
            return new AxeMan;
            break;
         default:
            return new LightMan;
      }
}