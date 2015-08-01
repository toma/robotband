#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include "Adafruit_NeoPixel.h"

PianoRoll pianoRoll;
extern Musician *musician;
unsigned char *stateSet;
unsigned char perPixelColors[10];
unsigned char pixelFlags;

String serialAction = "";
String inputString = "";

//TODO: Multiple medallions
int lightPin = 8;
Adafruit_NeoPixel medallion = Adafruit_NeoPixel(7, lightPin, NEO_GRB + NEO_KHZ800);

uint32_t purple = medallion.Color(36, 28, 153);
uint32_t blueish = medallion.Color(0, 0, 200);
uint32_t off = medallion.Color(0, 0, 0);

#define PIXEL_0     1
#define PIXEL_1     2
#define PIXEL_2     4
#define PIXEL_3     8
#define PIXEL_4     16
#define PIXEL_5     32
#define PIXEL_6     64

void setup() {
    Serial.begin(9600); // For debugging

    medallion.begin();
    medallion.show();

    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, OUTPUT);

    musician = Musician::makeMusician();
    musician->setup();

    musician->powerOnSelfTest();

    pianoRoll.init(musician);
}

uint32_t getPixelColor(unsigned char pixelNumber) {
    switch (perPixelColors[pixelNumber]) {
        case 0:
            return off;
        case 1:
            return purple;
        case 2:
            return blueish;
        default:
            return purple;
    }
}

void setPixelState(unsigned char flags, unsigned char pixelNumber, unsigned char definedPixel) {
    if ((definedPixel & flags) == definedPixel) {
        medallion.setPixelColor(pixelNumber, getPixelColor(pixelNumber));
    } else {
        medallion.setPixelColor(pixelNumber, off);
    }
}

// Fill the dots one after the other with a color
void displayMedallion(unsigned char flags, unsigned char *perPixelColors) {
//    Serial.print("FLAGS: ");
//    Serial.println(flags);

    setPixelState(flags, 0, PIXEL_0);
    setPixelState(flags, 1, PIXEL_1);
    setPixelState(flags, 2, PIXEL_2);
    setPixelState(flags, 3, PIXEL_3);
    setPixelState(flags, 4, PIXEL_4);
    setPixelState(flags, 5, PIXEL_5);
    setPixelState(flags, 6, PIXEL_6);

    medallion.show();
}

void loop() {

    if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        if (inputString.equalsIgnoreCase("STOP")) {
            pianoRoll.stop();
        } else if (inputString.equalsIgnoreCase("WHOAMI")) {
            Serial.println(musician->getFolderName());
        } else if (inputString.substring(0, 3).equals("HSF")) {
            //Set BPM in piano roll from HSFXX, where XXX is the BPM and play HSF.CSV
            Serial.println("HSF!");
            Serial.print("BPM: ");
            String bpm = inputString.substring(3, inputString.length());
            pianoRoll.overrideBPM(bpm.toInt());
            pianoRoll.loadSong("HSF.CSV");
        } else {
            pianoRoll.loadSong(inputString);
        }
    }
    stateSet = pianoRoll.getStateSet();
    int loopDelay = pianoRoll.getDelay();

    musician->setState(stateSet[0], stateSet[1]);

    pixelFlags = stateSet[2];
    perPixelColors[0] = stateSet[3];
    perPixelColors[1] = stateSet[4];
    perPixelColors[2] = stateSet[5];
    perPixelColors[3] = stateSet[6];
    perPixelColors[4] = stateSet[7];
    perPixelColors[5] = stateSet[8];
    perPixelColors[6] = stateSet[9];

    displayMedallion(pixelFlags, perPixelColors);

    delay(pianoRoll.getDelay());

}
