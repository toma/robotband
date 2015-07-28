#ifndef CONDUCTOR_LEADGUITARIST_H
#define CONDUCTOR_LEADGUITARIST_H

#include "Arduino.h"
#include "AxeMan.h"

class LeadGuitarist: public AxeMan {
public:
    String getFolderName();
};

#endif //CONDUCTOR_LEADGUITARIST_H
