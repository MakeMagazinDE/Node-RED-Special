#include <Servo.h>

Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(D2);
}

void loop() {
  Serial.println("Rechts rum");
  for (int16_t pos = 0; pos <= 180; pos++) {
    servo.write(pos);
    delay(15);
  }
  
  Serial.println("Links rum");
  for (int16_t pos = 180; pos >= 0; pos--) {
    servo.write(pos);
    delay(15);
  }
}
