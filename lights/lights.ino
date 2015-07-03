// PIN CONFIGURATION
const unsigned char leftLightPin = 9;
const unsigned char rightLightPin = 10;

// ACTION KEY
const unsigned char states = 2;
const unsigned char delayKey = 0;
const unsigned char leftLightKey = 1;
const unsigned char rightLightKey = 2;

// Global Vars
int currentPhrase = 0;
unsigned char delayTime = 100;

// Test Show
const int testSize = 500;
unsigned char stateArray[states+1][testSize];

void setup() 
{ 
  Serial.begin(9600);
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);

  int fillCounter = 0;

  while (fillCounter < testSize) {
    stateArray[delayKey][fillCounter] = 100;
    stateArray[leftLightKey][fillCounter] = fillCounter % 2;
    stateArray[rightLightKey][fillCounter] = (fillCounter + 1) % 2;
    fillCounter++;
  }
} 
 
void loop() 
{ 
  setState(leftLightPin, leftLightKey);
  setState(rightLightPin, rightLightKey);

  delayTime = getDelay();
  delay(delayTime);
  currentPhrase++;
}

void setState(unsigned char pin, unsigned char state) {
  if (getCurrentState(state)) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

unsigned char getDelay() {
  return stateArray[delayKey][currentPhrase];
}

bool getCurrentState(int actionIndex){
  return stateArray[actionIndex][currentPhrase];
}