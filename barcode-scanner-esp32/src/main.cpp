#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(18, 19); // RX = Richtung USB-Connectors, TX = Richtung Scanner
LiquidCrystal_I2C lcd(0x27,16,2);

char text[15] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int count = 0;
 
void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);  
  mySerial.begin(9600);
}
 
void loop()
{
  if (mySerial.available()) // Check if there is Incoming Data in the Serial Buffer.
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    while (mySerial.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = mySerial.read(); // Read 1 Byte of data and store it in a character variable
      Serial.print(input); // Print the Byte
      lcd.print(input);
    }
  }
}
