#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <Adafruit_NeoPixel.h>

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_SI1145 uv = Adafruit_SI1145();

//button
int buttonPin = 6;
int buttonPinValue = 0;
int speaker = 1; // piezo wired to FLORA TX
int state = 0;
int markerTime = 0;
int previousVal = 0;


void setup()
{
    pinMode(speaker, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
    delay(2000);

}

void loop()
{
    Serial.println("===================");

    buttonPinValue = digitalRead(buttonPin);
    // Serial.println(buttonPinValue);

    nextStateChange();

    switch (state)
    {
    case 1:
        // statements
        Serial.println("first");
        colorWipe(strip.Color(255, 255, 255), 500);
        break;
    case 2:
        colorWipe(strip.Color(0, 100, 255), 500);

        // statements
        break;
        case 3:
        Serial.println("second");
        // statements
        break;
    default:
        // statements
        Serial.println("default");
        state = 0;
    }


}



void nextStateChange()
{
    buttonPinValue = digitalRead(buttonPin);
    Serial.print("previousVal");
    Serial.println(previousVal);
        Serial.print("state");
    Serial.println(state);
    if(buttonPinValue == 1 && previousVal == 1)
    {
      Serial.println("working");
        state = state+1;
        previousVal = 0;
    }

    if(buttonPinValue == 0)
    {
        previousVal = 1;
    }

}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}