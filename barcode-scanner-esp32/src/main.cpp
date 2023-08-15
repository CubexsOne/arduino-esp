#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h> 

SoftwareSerial mySerial(16, 17); // RX = Richtung USB-Connectors, TX = Richtung Scanner
 
void setup()
{
  Serial.begin(9600);  
  mySerial.begin(9600);
}
 
void loop()
{
  if (mySerial.available()) // Check if there is Incoming Data in the Serial Buffer.
  {
    while (mySerial.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = mySerial.read(); // Read 1 Byte of data and store it in a character variable
      Serial.print(input); // Print the Byte
    }
  }
}
