#include "Arduino.h"
#include "LightMan.h"
#include "Drummer.h"
#include "LeadGuitarist.h"
#include "RhythmGuitarist.h"

Musician *Musician::makeMusician() {
    //Use 5, 6 and 7 to determine binary value of musician, 5V into the pin means it's on
    unsigned char pin5Value = digitalRead(5);
    unsigned char pin6Value = digitalRead(6);
    unsigned char pin7Value = digitalRead(7);

    unsigned char bitValue = pin5Value + (pin6Value * 2) + (pin7Value * 4);

    Serial.print("Musician Jumper Bit Value: ");
    Serial.println(bitValue);

    switch (bitValue) {
        case 0:
            return new LightMan;
        case 1:
            return new LeadGuitarist;
        case 2:
            return new RhythmGuitarist;
        case 4:
            return new Drummer;
        default:
            return new LightMan;
    }
}
