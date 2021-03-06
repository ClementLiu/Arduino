// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

int delayval = 200; // delay for half a second
int sensorPin=7;
boolean val =0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
// #if defined (__AVR_ATtiny85__)
//   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
// #endif
  // End of trinket special code
  pinMode(sensorPin, INPUT);

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show(); // This initializes the NeoPixel library.
  // Serial.begin (9600);
}

// int      head  = 0, tail = -10;
uint32_t color = 0xFF0000;  
uint32_t black = 0x000000;      // 'On' color (starts red)
int countNumberSound = 0;

void loop() {
  val =digitalRead(sensorPin);
  Serial.println (val);
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  // for(int i=0;i<NUMPIXELS;i++){

  //   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //   pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

  //   pixels.show(); // This sends the updated pixel color to the hardware.


  // }
  if(val == 0){
      for(int i=0; i<NUMPIXELS; i++){
          pixels.setPixelColor(i, color);
      }
      pixels.show();
      countNumberSound = 0;
      delay(2000);
  }else{
    for(int i=0; i<NUMPIXELS; i++){
        pixels.setPixelColor(i, black);
    }
    pixels.show();
    if(countNumberSound == 0){
          delay(10);
          countNumberSound =1;
        }
  }
  
}

