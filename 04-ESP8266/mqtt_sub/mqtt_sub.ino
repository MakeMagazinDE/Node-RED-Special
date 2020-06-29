#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "<SSID des eigenen WLAN>";
const char* PASSWORD = "<Passwort des eigenen WLAN>";
const char* MQTT_SERVER = "<IP-Adresse oder Namen des MQTT-Brokers>";
const char* MQTT_TOPIC = "home/LED";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

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

void handleMessage(char* topic, byte* payload, unsigned int length) {
  Serial.printf("Eingehende Nachricht [%s]: ", topic);
  for (uint16_t i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void setup() {
  randomSeed(micros());
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.begin(115200);
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(handleMessage);
}

void loop() {
  reconnect();
  mqttClient.loop();
}
