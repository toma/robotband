#include "Arduino.h"
#include "Lights.h"
#include "Adafruit_NeoPixel.h"

int HALO_PIN = 3;
int MEDALLION_PIN = 4;

int blue = 1;
int yellow = 2;
int purple = 3;



Adafruit_NeoPixel halo = Adafruit_NeoPixel(6, HALO_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel medallion = Adafruit_NeoPixel(7, MEDALLION_PIN, NEO_GRB + NEO_KHZ800);

void Lights::setLights(String lightValue) {
    // HALO QUADRANT 1 COLOR | HQ1 brightness | HQ2 COLOR | HQ2 bright ...
    Serial.print("LIGHT PARTS: ");
    Serial.println(lightVaue);
//    String
}

