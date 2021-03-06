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

// add HSL  to RGB 
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





void loop()
{
  
// led part

if (peakToPeak >= 0 && peakToPeak<200)
{
  /* code */
  Serial.println("peakToPeak");
  color = 0x00FF00;
  }else if(peakToPeak >= 201 && peakToPeak < 400){
  color=0xFF0000;
  }else if (peakToPeak >= 401 && peakToPeak < 600){
  color=0xFFFFFF;
  }else if (peakToPeak >= 601 && peakToPeak < 800){
  color=0x88FF00;
  }else if(peakToPeak >= 801 && peakToPeak < 1023){
  color=0xFF00FF;
  }


addcolor(color, 100);


  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
   // if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
    // color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

  // led part end

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
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts


  Serial.println(peakToPeak);
  // if (peakToPeak < 200)
  // {
  //   //Go straight
  //   digitalWrite(3, HIGH); // this is the slowest my motor would still turn
    
  //   delay(100);
  //   Serial.println(peakToPeak);
  // }
  // else
  // {
  //   // Turn left
  //   digitalWrite(3, LOW); // motor off
  //     delay(100);
  //   Serial.println(peakToPeak);
  // }

}


//     // Initialize for a Fade
//     void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD)
//     {
//         ActivePattern = FADE;
//         Interval = interval;
//         TotalSteps = steps;
//         Color1 = color1;
//         Color2 = color2;
//         Index = 0;
//         Direction = dir;
//     }

// // Update the Fade Pattern
//     void FadeUpdate()
//     {
//         uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
//         uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
//         uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
//         ColorSet(Color(red, green, blue));
//         show();
//         Increment();
//     }



// updata color function 
int addcolor(uint32_t colorInUse, int delayTime){
  for (int i = 0; i < NUMPIXELS; ++i)
  {
  /* code */
  strip.setPixelColor(i, colorInUse); // 'On' pixel at head
 // strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
                 
  }
    delay(delayTime);  
         // Pause 20 milliseconds (~50 FPS)
}










