#include "Adafruit_NeoPixel.h"

String serialAction = "";
String inputString = "";

//TODO: Multiple medallions
int lightPin = 8;
Adafruit_NeoPixel medallion = Adafruit_NeoPixel(7, lightPin, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(9600); // For debugging

    medallion.begin();
    medallion.show();

    pinMode(8, OUTPUT);

}

void displayMedallion(uint32_t color) {
    for (int i = 0; i < 7; i++) {
        medallion.setPixelColor(i, color);
    }
    medallion.show();
}

void loop() {

    if (Serial.available() > 0) {
        inputString = Serial.readStringUntil('\n');
        int red = getValueFromString(inputString, ',', 0);
        int green = getValueFromString(inputString, ',', 1);
        int blue = getValueFromString(inputString, ',', 2);
        Serial.print("red: ");
        Serial.println(red);

        Serial.print("green: ");
        Serial.println(green);

        Serial.print("blue: ");
        Serial.println(blue);
        displayMedallion(medallion.Color(red, green, blue));
    }

    delay(100);
}

int getValueFromString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length()-1;
    for(int i=0; i<=maxIndex && found<=index; i++){
        if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]).toInt() : -1;
}

