#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "raspberrypi";
const char* PASSWORD = "pi1234";
const char* MQTT_SERVER = "192.168.178.38";
const char* MQTT_SERVER = "node-red";
const char* MQTT_TOPIC = "home/MQTT-Test";
const uint16_t MESSAGE_LEN = 50;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
uint32_t lastTimestamp = 0;
uint32_t messageId = 0;

void setupWifi() {
  delay(10);
  Serial.printf("Starte Verbindung mit %s.\n", SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("Verbunden mit %s.\n", SSID);
  Serial.printf("IP-Adresse: %s.\n", WiFi.localIP().toString().c_str());
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Suche den MQTT-Broker...");
    String clientId = "MQTT-Client-" + String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.printf("verbunden als %s.\n", clientId.c_str());
      mqttClient.subscribe(MQTT_TOPIC);
    } else {
      Serial.printf("Fehlercode: %d.", mqttClient.state());
      Serial.println(" Neuer Versuch in 5 Sekunden.");
      delay(5000);
    }
  }
}

void setup() {
  randomSeed(micros());
  Serial.begin(115200);
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, 1883);
}

void loop() {
  char message[MESSAGE_LEN];

  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  uint32_t now = millis();
  if (now - lastTimestamp > 2000) {
    lastTimestamp = now;
    snprintf(message, MESSAGE_LEN, "Nachricht #%ld", ++messageId);
    Serial.printf("Sende Nachricht: %s\n", message);
    mqttClient.publish(MQTT_TOPIC, message);
  }
}
