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
  if (state[leftLightKey] == 1) {
    digitalWrite(leftLightPin, HIGH);
  } else {
    digitalWrite(leftLightPin, LOW);
  }

  if (state[rightLightKey] == 1) {
    digitalWrite(rightLightPin, HIGH);
  } else {
    digitalWrite(rightLightPin, LOW);
  }
}