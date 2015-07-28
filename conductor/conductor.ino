#include "PianoRoll.h"
#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include "Adafruit_NeoPixel.h"

PianoRoll pianoRoll;
extern Musician *musician;
unsigned char *stateSet;
unsigned char pixelFlags;
uint32_t pixelColor = 0;

uint32_t colors[3];

int RED = 0;
int GREEN = 1;
int BLUE = 2;

String serialAction = "";
String inputString = "";

int lightPin = 8;
Adafruit_NeoPixel medallion = Adafruit_NeoPixel(7, lightPin, NEO_GRB + NEO_KHZ800);

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

void checkPixelOn(unsigned char flags, unsigned char pixelNumber, unsigned char definedPixel, uint32_t color) {
    if ((definedPixel & flags) == definedPixel) {
        medallion.setPixelColor(pixelNumber, color);
//        Serial.print("Turning on pixel: ");
//        Serial.println(pixelNumber);
    } else {
        medallion.setPixelColor(pixelNumber, medallion.Color(0, 0, 0));
    }
}

// Fill the dots one after the other with a color
void displayMedallion(unsigned char flags, uint32_t color) {

    Serial.print("FLAGS: ");
    Serial.println(flags);

    checkPixelOn(flags, 0, PIXEL_0, color);
    checkPixelOn(flags, 1, PIXEL_1, color);
    checkPixelOn(flags, 2, PIXEL_2, color);
    checkPixelOn(flags, 3, PIXEL_3, color);
    checkPixelOn(flags, 4, PIXEL_4, color);
    checkPixelOn(flags, 5, PIXEL_5, color);
    checkPixelOn(flags, 6, PIXEL_6, color);

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
    pianoRoll.readLine();
    stateSet = pianoRoll.getStateSet();
    int loopDelay = pianoRoll.getDelay();

    musician->setState(stateSet[0], stateSet[1]);

    pixelFlags = stateSet[2];
    pixelColor = stateSet[3];

    if (pixelColor == 1) {
        colors[RED] = 255;
        colors[GREEN] = 0;
        colors[BLUE] = 0;
    } else if (pixelColor == 2) {
        colors[RED] = 0;
        colors[GREEN] = 255;
        colors[BLUE] = 0;
    }

    displayMedallion(pixelFlags, medallion.Color(colors[RED], colors[GREEN], colors[BLUE]));

    delay(pianoRoll.getDelay());

}
