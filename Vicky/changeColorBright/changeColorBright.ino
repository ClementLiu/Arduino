const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;

int micsensor = A0; // Attach the Soundsensor to analogRead pin A0
int micsensorVal = 0; // Attach the Soundsensor to analogRead pin A0

// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

unsigned int peakToPeak = 0;   // peak-to-peak level



#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 30 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

// add HSL to rgb 

const byte dim_curve[] = {
    0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
    3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
    6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
    11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
    15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
    20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
    27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
    36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
    48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
    63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
    83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};
int sensorVal = 0; // store the value coming from the sensor
int fadeVal   = 0; // value that changes between 0-255
int fadeSpeed = 5; // 'speed' of fading

// getRGB function stores RGB values in this array
// use these values for the red, blue, green led. 
int rgb_colors[3]; 

int hue, saturation, brightness;



void setup()
{
  Serial.begin(9600);
  pinMode(micsensor, INPUT); // Declare the knock as Input
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif




  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int      head  = 0, tail = -3; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      //





void loop(){
  
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  unsigned long start = millis(); // Start of sample window


  // collect data for 250 miliseconds
  while (millis() - start < sampleWindow)
  {
    micsensorVal = analogRead(A0);
    if (micsensorVal < 1024)  //This is the max of the 10-bit ADC so this loop will include all readings
    {
      if (micsensorVal > signalMax)
      {
        signalMax = micsensorVal;  // save just the max levels
      }
      else if (micsensorVal < signalMin)
      {
        signalMin = micsensorVal;  // save just the min levels
      }
    }

    if (peakToPeak >= 0 && peakToPeak<200)
  {
  /* code */
  Serial.println("peakToPeak");
  fadingColor(100);
  }else if(peakToPeak >= 201 && peakToPeak < 400){
  // color=0xFF0000;
  fadingColor(200);
  }else if (peakToPeak >= 401 && peakToPeak < 600){
  fadingColor(50);
  }else if (peakToPeak >= 601 && peakToPeak < 800){
  fadingColor(10);
  }else if(peakToPeak >= 801 && peakToPeak < 1023){
  fadingColor(300);
  }

    
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts


  Serial.println(peakToPeak);

}

// updata color function 
int addcolor(int colorR,int colorG,int colorB, int delayTime){
  for (int i = 0; i < NUMPIXELS; ++i)
  {
  /* code */
  strip.setPixelColor(i, colorR,colorG,colorB); // 'On' pixel at head
 // strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
                 
  }
    delay(delayTime);  
//    Serial.println("work");
         // Pause 20 milliseconds (~50 FPS)
}

void fadingColor(int hueFade){
  fadeVal = fadeVal + fadeSpeed;         // change fadeVal by speed
  fadeVal = constrain(fadeVal, 0, 255);  // keep fadeVal between 0 and 255

  if(fadeVal==255 || fadeVal==0)         // change from up>down or down-up (negative/positive)
  { fadeSpeed = -fadeSpeed;  
  }  

  // hue        = map(sensorVal,0, 1023,0, 359);     // hue is a number between 0 and 360
  hue        = hueFade;     // hue is a number between 0 and 360
  saturation = 255;                               // saturation is a number between 0 - 255
  brightness = fadeVal;                           // value is a number between 0 - 255

  getRGB(hue,saturation,brightness,rgb_colors);   // converts HSB to RGB



  addcolor(rgb_colors[0],rgb_colors[1],rgb_colors[2], 0);
  Serial.println(rgb_colors[1]);

}

void fadeLED(){
  for (int i = 0; i < NUMPIXELS; ++i)
  {
    /* code */
    uint32_t colorLED; 
    colorLED = strip.GetPixelColor(i);
    
  }
  
}
// change to RGB 
void getRGB(int hue, int sat, int val, int colors[3]) { 
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.      
  */

  val = dim_curve[val];
  sat = 255-dim_curve[255-sat];

  int r;
  int g;
  int b;
  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;  
  } else  { 

    base = ((255 - sat) * val)>>8;

    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;

    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;

    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;

    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;

    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;

    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }

    colors[0]=r;
    colors[1]=g;
    colors[2]=b; 
  }   
}







