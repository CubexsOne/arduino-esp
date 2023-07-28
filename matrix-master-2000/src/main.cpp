#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include "wavehc.h"

ArduinoLEDMatrix matrix;
void setup() {
  Serial.begin(9600);
  matrix.loadSequence(wavehc);
  matrix.begin();

  matrix.play(true);
}

void loop() {}