#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

const char* SSID = "<SSID des eigenen WLAN>";
const char* PASSWORD = "<Passwort des eigenen WLAN>";
const char* MQTT_SERVER = "<IP-Adresse oder Namen des MQTT-Brokers>";
const char* CLIENT_ID = "Data-Rate-Meter";
const char* MQTT_TOPIC_DOWNLOAD = "stats/download-data-rate";

const uint8_t NUM_PIXELS = 20;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Adafruit_NeoPixel downloadMeter(NUM_PIXELS, D2, NEO_GRB + NEO_KHZ800);

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
      mqttClient.subscribe(MQTT_TOPIC_DOWNLOAD);
    } else {
      Serial.printf("Fehlercode: %d.", mqttClient.state());
      Serial.println(" Neuer Versuch in 5 Sekunden.");
      delay(5000);
    }
  }
}

void handleMessage(char* topic, byte* payload, unsigned int length) {
  Serial.printf("Eingehende Nachricht [%s]: ", topic);
  String message;
  for (uint16_t i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  uint8_t downloadRate = message.toInt();
  Serial.println(downloadRate);
  showDataRate(downloadRate);
}

const uint32_t PIXEL_COLORS[NUM_PIXELS] = {
  // Green
  downloadMeter.Color(0, 20, 0),  downloadMeter.Color(0, 20, 0),
  downloadMeter.Color(0, 20, 0),  downloadMeter.Color(0, 20, 0),
  downloadMeter.Color(0, 20, 0),  downloadMeter.Color(0, 20, 0),
  downloadMeter.Color(0, 20, 0),  downloadMeter.Color(0, 20, 0),
  downloadMeter.Color(0, 20, 0),  downloadMeter.Color(0, 20, 0),
  // Yellow
  downloadMeter.Color(20, 20, 0), downloadMeter.Color(20, 20, 0),
  downloadMeter.Color(20, 20, 0), downloadMeter.Color(20, 20, 0),
  downloadMeter.Color(20, 20, 0), downloadMeter.Color(20, 20, 0),
  // Red
  downloadMeter.Color(20, 0, 0),  downloadMeter.Color(20, 0, 0),
  downloadMeter.Color(20, 0, 0),  downloadMeter.Color(20, 0, 0),
};

void showDataRate(const uint8_t percentage) {
  downloadMeter.clear();
  downloadMeter.show();
  const uint8_t numPixels = round(percentage / 5.0);
  for (uint8_t i = 0; i < numPixels; i++) {
    downloadMeter.setPixelColor(i, PIXEL_COLORS[i]);
    downloadMeter.show();
  }
}

void setup() {
  Serial.begin(115200);
  setupWifi();
  downloadMeter.begin();
  downloadMeter.clear();
  downloadMeter.show();
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(handleMessage);
}

void loop() {
  reconnect();
  mqttClient.loop();
}
