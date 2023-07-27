#include <WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

// Declarations
void setup_wifi();
void reconnect();
void callback(char*, byte*, unsigned int);
void sendMQTTMessage(const char*);

// WiFi
const char* wifi_ssid = WIFI_SSID;
const char* wifi_password = WIFI_PASSWORD;

// MQTT
const char* mqtt_server = MQTT_HOST;
const int mqtt_port = 1883;
const char* mqtt_user = MQTT_USER;
const char* mqtt_password = MQTT_PASSWORD;
const char* mqtt_topic = MQTT_TOPIC;
bool send = false;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  Serial.println(wifi_ssid);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (client.connected()) {
    if (!send) {
      send = true;
      sendMQTTMessage("ABC");
    }
  }
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Nachricht empfangen von Topic [");
  Serial.print(topic);
  Serial.print("] Daten: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void sendMQTTMessage(const char* message) {
  if (!client.connected()) {
    reconnect();
  }
  client.publish(mqtt_topic, message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Verbinde zum MQTT-Broker...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("verbunden");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Fehlgeschlagen, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
