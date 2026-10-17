#include <Arduino.h>
#include "../src/config.h"

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  
  // Setup sensor pin sebagai input
  pinMode(SENSOR_PIN, INPUT);
  
  Serial.println("=== ADC Sensor Test ===");
  Serial.println("Membaca nilai RAW dari kedua sensor...");
  Serial.println();
}

void loop() {
  // Baca nilai RAW ADC dari Sensor (GPIO 34)
  int sensor_raw = analogRead(SENSOR_PIN);
  
  // Contoh map: scaling dari range ADC ke 0-100%
  int scaled = map(sensor_raw, 0, ADC_MAX, 0, 100);
  
  // Tampilkan hasil
  Serial.print("Sensor Raw: ");
  Serial.print(sensor_raw);
  Serial.print(" -> Scaled: ");
  Serial.print(scaled);
  Serial.println("%");
  
  delay(2000); // Baca setiap 2 detik
}
