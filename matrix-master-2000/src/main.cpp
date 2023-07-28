#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include <WiFiS3.h>

void setup_wifi();

const char* wifi_ssid = "";
const char* wifi_password = "";

ArduinoLEDMatrix matrix;
byte frame[8][12] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

void setup() {
  Serial.begin(9600);
  matrix.begin();
  setup_wifi();
}

void loop() {
  matrix.renderBitmap(frame, 8, 12);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Verbinde mit WiFi-Netzwerk: ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi verbunden");
  Serial.println("IP-Adresse: ");
  Serial.println(WiFi.localIP());
}