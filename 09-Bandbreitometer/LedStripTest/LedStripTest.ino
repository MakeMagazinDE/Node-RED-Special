#include <Adafruit_NeoPixel.h>

const uint8_t NUM_PIXELS = 20;
const uint16_t DELAY = 50;

Adafruit_NeoPixel pixels(NUM_PIXELS, D2, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
  pixels.clear();
  for (uint8_t i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(10, 0, 0));
    pixels.show();
    delay(DELAY);
  }

  pixels.clear();
  for (int8_t i = NUM_PIXELS - 1; i >= 0; i--) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 10));
    pixels.show();
    delay(DELAY);
  }
}
