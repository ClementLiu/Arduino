/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates the available gamut of barcodes.
  See 'A_printertest' sketch for a more generalized printing example.

  BARCODE AVAILABILITY VARIES WITH FIRMWARE.  Not all barcodes may be
  displayed, this is normal.  Sketch may need changes for older firmware.
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"

// Here's the syntax when using SoftwareSerial (e.g. Arduino Uno) --------
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(9600);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)

  printer.justify('C');

  // There seems to be some conflict between datasheet descriptions
  // of barcode formats and reality.  Try Wikipedia and/or:
  // http://www.barcodeisland.com/symbolgy.phtml

  // Also note that strings passed to printBarcode() are always normal
  // RAM-resident strings; PROGMEM strings (e.g. F("123")) are NOT used.
  printer.setBarcodeHeight(10);

  // CODE 93: compressed version of Code 39?
  printer.print(F("CODE 93:"));
  for (int i=0; i <= 20; i++){
      printer.printBarcode("GGGYYYYGGG", CODE93);
      delay(10);
}

  
//  printer.printBarcode("ADAFRUIT", CODE93);

  // CODE 128: 2-255 characters (ASCII 0-127)
  printer.print(F("CODE128:"));
  printer.printBarcode("Adafruit", CODE128);

  printer.setDefault(); // Restore printer to defaults
}

void loop() {
}
