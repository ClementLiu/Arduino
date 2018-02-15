////////////////////////////////////////////////////////////////////////
// Arduino Bluetooth Interface with Brainsense
//
// This is example code provided by Pantech Prolabs. and is provided
// license free.
////////////////////////////////////////////////////////////////////////
#include <Servo.h>      


#define LED 13
#define BAUDRATE 57600
#define DEBUGOUTPUT 0

#define GREENLED1  3
#define GREENLED2  4
#define GREENLED3  5
#define YELLOWLED1 6
#define YELLOWLED2 7
#define YELLOWLED3 8
#define YELLOWLED4 9
#define REDLED1    10
#define REDLED2    11
#define REDLED3    12

#define powercontrol 10

// checksum variables
byte generatedChecksum = 0;
byte checksum = 0;
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;

//////////////////////////
// Microprocessor Setup //
//////////////////////////


// server/
Servo servoLeft;       
void setup()

{

servoLeft.attach(13);                      // Attach left signal to pin 13
  // servoLeft.writeMicroseconds(1500); 

  pinMode(GREENLED1, OUTPUT);
  pinMode(GREENLED2, OUTPUT);
  pinMode(GREENLED3, OUTPUT);
  pinMode(YELLOWLED1, OUTPUT);
  pinMode(YELLOWLED2, OUTPUT);
  pinMode(YELLOWLED3, OUTPUT);
  pinMode(YELLOWLED4, OUTPUT);
  pinMode(REDLED1, OUTPUT);
  pinMode(REDLED2, OUTPUT);
  pinMode(REDLED3, OUTPUT);

  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);           // USB
}

////////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte()

{
  int ByteRead;
  while (!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT
  Serial.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////
//MAIN LOOP//
/////////////
void loop()

{
  // Look for sync bytes
  if (ReadOneByte() == 170)
  {
    if (ReadOneByte() == 170)
    {
      payloadLength = ReadOneByte();

      if (payloadLength > 169)                     //Payload length can not be greater than 169
        return;
      generatedChecksum = 0;
      for (int i = 0; i < payloadLength; i++)
      {
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
      }

      checksum = ReadOneByte();                      //Read checksum byte from stream
      generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

      if (checksum == generatedChecksum)
      {
        poorQuality = 200;
        attention = 0;
        meditation = 0;

        for (int i = 0; i < payloadLength; i++)
        { // Parse the payload
          switch (payloadData[i])
          {
          case 2:
            i++;
            poorQuality = payloadData[i];
            bigPacket = true;
            break;
          case 4:
            i++;
            attention = payloadData[i];
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT

        // *** Add your code here ***

        if (bigPacket)
        {
          if (poorQuality == 0)
            digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);

          Serial.print("PoorQuality: ");
          Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" Time since last packet: ");
          Serial.print(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();
          Serial.print("\n");

          switch (attention / 10)
          {
          case 0:
            Serial.println("Not Move");
            servoLeft.write(0);  
            break;
          case 1:
            Serial.println("Not Move");
            servoLeft.write(0);  
            break;
          case 2:
            Serial.println("Not Move");
            servoLeft.write(0);  
            break;
          case 3:
            Serial.println("Move");
            servoLeft.write(180);
            break;
          case 4:
            Serial.println("Move");
            servoLeft.write(180);
            break;
          case 5:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          case 6:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          case 7:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          case 8:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          case 9:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          case 10:
            Serial.println(" Move");
            servoLeft.write(180);
            break;
          }
        }
#endif
        bigPacket = false;
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}


