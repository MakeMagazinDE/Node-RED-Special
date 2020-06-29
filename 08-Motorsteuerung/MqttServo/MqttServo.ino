#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* SSID = "<SSID des eigenen WLAN>";
const char* PASSWORD = "<Passwort des eigenen WLAN>";
const char* MQTT_SERVER = "<IP-Adresse oder Namen des MQTT-Brokers>";
const char* CLIENT_ID = "Temperatur-Servo";
const char* MQTT_TOPIC = "Servo";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Servo servo;

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
  String positionString;
  for (uint16_t i = 0; i < length; i++) {
    positionString += (char)payload[i];
  }
  Serial.println(positionString);
  int16_t position = positionString.toInt();
  servo.write(position);
}

void setup() {
  Serial.begin(115200);
  servo.attach(D2);
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(handleMessage);
}

void loop() {
  reconnect();
  mqttClient.loop();
}
