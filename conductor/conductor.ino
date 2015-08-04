#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include "Adafruit_NeoPixel.h"

PianoRoll pianoRoll;
extern Musician *musician;
unsigned char *stateSet;
unsigned char perPixelColors[7];
unsigned char pixelFlags;

String serialAction = "";
String inputString = "";

//TODO: Multiple medallions
int lightPin = 8;
Adafruit_NeoPixel medallion = Adafruit_NeoPixel(7, lightPin, NEO_GRB + NEO_KHZ800);

uint32_t dimWhite = medallion.Color(200, 200, 255);
uint32_t darkTeal = medallion.Color(0, 45, 45);
uint32_t brightTeal = medallion.Color(0, 255, 255);
uint32_t purple = medallion.Color(255, 0, 255);
uint32_t violet = medallion.Color(125, 0, 255);
uint32_t red = medallion.Color(255, 0, 0);
uint32_t fireRed = medallion.Color(255, 30, 15);
uint32_t gold = medallion.Color(175, 100, 0);
uint32_t darkGreen = medallion.Color(0, 255, 0);
uint32_t lightGreen = medallion.Color(25, 255, 25);
uint32_t green = medallion.Color(50, 255, 50);


uint32_t off = medallion.Color(0, 0, 0);

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
            return dimWhite;
        case 2:
            return darkTeal;
        case 3:
            return brightTeal;
        case 4:
            return purple;
        case 5:
            return violet;
        case 6:
            return red;
        case 7:
            return fireRed;
        case 8:
            return gold;
        case 9:
            return darkGreen
        case 10:
            return green
        case 11:
            return lightGreen
        default:
            return off;
    }
}

void setPixelState(unsigned char pixelNumber) {
    medallion.setPixelColor(pixelNumber, getPixelColor(pixelNumber));
}

// Fill the dots one after the other with a color
void displayMedallion() {
    setPixelState(0);
    setPixelState(1);
    setPixelState(2);
    setPixelState(3);
    setPixelState(4);
    setPixelState(5);
    setPixelState(6);

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

    perPixelColors[0] = stateSet[2];
    perPixelColors[1] = stateSet[3];
    perPixelColors[2] = stateSet[4];
    perPixelColors[3] = stateSet[5];
    perPixelColors[4] = stateSet[6];
    perPixelColors[5] = stateSet[7];
    perPixelColors[6] = stateSet[8];

    displayMedallion();

    delay(pianoRoll.getDelay());

}
