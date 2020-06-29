void setup() {
  pinMode(D2, INPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println(digitalRead(D2));
  delay(50);
}
