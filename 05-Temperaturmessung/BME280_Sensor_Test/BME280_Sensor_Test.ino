#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Serial.println("BME280-Test");

  if (!bme.begin(0x76)) {
    Serial.println("Konnte keinen BME280-Sensor finden!");
    while (1)
      delay(10);
  }
}

void loop() { 
  Serial.printf("Temperatur = %.2f C\n", bme.readTemperature());
  Serial.printf("Luftdruck = %.2f hPa\n", bme.readPressure() / 100.0F);
  Serial.printf("Luftfeuchtigkeit = %.2f %%\n", bme.readHumidity());
  Serial.println();
  delay(1000);
}
