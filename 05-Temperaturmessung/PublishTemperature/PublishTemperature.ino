#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const char* SSID = "<SSID des eigenen WLAN>";
const char* PASSWORD = "<Passwort des eigenen WLAN>";
const char* MQTT_SERVER = "<IP-Adresse oder Namen des MQTT-Brokers>";
const char* CLIENT_ID = "Temp-Schlafzimmer";
const char* TEMP_TOPIC = "temp/schlafzimmer";
const uint16_t MESSAGE_LEN = 10;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
uint32_t lastTimestamp = 0;
Adafruit_BME280 bme;

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
    if (mqttClient.connect(CLIENT_ID)) {
      Serial.printf("verbunden als %s.\n", CLIENT_ID);
    } else {
      Serial.printf("Fehlercode: %d.", mqttClient.state());
      Serial.println(" Neuer Versuch in 5 Sekunden.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  if (!bme.begin(0x76)) {
    Serial.println("Konnte keinen BME280-Sensor finden!");
    while (1)
      delay(10);
  }
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, 1883);
}

void loop() {
  reconnect();
  mqttClient.loop();

  const uint32_t now = millis();
  if (now - lastTimestamp > 2000) {
    char message[MESSAGE_LEN];
    lastTimestamp = now;
    snprintf(message, MESSAGE_LEN, "%.2f", bme.readTemperature());
    Serial.printf("Sende Nachricht: %s\n", message);
    mqttClient.publish(TEMP_TOPIC, message);
  }
}
