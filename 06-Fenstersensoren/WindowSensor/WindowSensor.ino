#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "<SSID des eigenen WLAN>";
const char* PASSWORD = "<Passwort des eigenen WLAN>";
const char* MQTT_SERVER = "<IP-Adresse oder Namen des MQTT-Brokers>";
const char* CLIENT_ID = "Fenster-Kueche";
const char* MQTT_TOPIC = "fenster/kueche";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
uint32_t lastTimestamp = 0;

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
  pinMode(D2, INPUT);
  Serial.begin(115200);
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, 1883);
}

void loop() {
  reconnect();
  mqttClient.loop();

  const uint32_t now = millis();
  if (now - lastTimestamp > 5 * 60 * 1000) {
    lastTimestamp = now;
    if (digitalRead(D2) == 0) {
      Serial.println("Das Küchenfenster ist auf.");
      mqttClient.publish(MQTT_TOPIC, "0");
    } else {
      Serial.println("Das Küchenfenster ist zu.");
      mqttClient.publish(MQTT_TOPIC, "1");
    }
  }
}
