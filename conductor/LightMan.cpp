#include <Arduino.h>
#include "LightMan.h"
// PIN CONFIGURATION
const unsigned char leftLightPin = 9;
const unsigned char rightLightPin = 10;

// ACTION KEY
const unsigned char leftLightKey = 0;
const unsigned char rightLightKey = 1;

void LightMan::setup() 
{ 
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);
} 
 
void LightMan::setState(unsigned char state[2]) 
{ 
  setLightState(leftLightPin, state[leftLightKey]);
  setLightState(rightLightPin, state[rightLightKey]);
}

void LightMan::setLightState(unsigned char pin, unsigned char lightState) {
  if (lightState == 1) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}