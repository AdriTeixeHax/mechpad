void setup() {
  Serial.begin(115200);
  Serial.println("Hello from ESP32-S3!");
}

void loop() {
  Serial.println("Still running...");
  delay(1000);
}
