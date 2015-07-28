#ifndef CONDUCTOR_RHYTHMGUITARIST_H
#define CONDUCTOR_RHYTHMGUITARIST_H

#include "Arduino.h"
#include "AxeMan.h"

class RhythmGuitarist: public AxeMan {
public:
    String getFolderName();
};

#endif //CONDUCTOR_RHYTHMGUITARIST_H
