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
  
  // Konversi ke persentase kelembapan (0-100%)
  int moisture = map(sensor_raw, SENSOR_DRY_ADC, SENSOR_WET_ADC, 0, 100);
  
  // Tampilkan hasil
  Serial.print("Sensor Raw: ");
  Serial.print(sensor_raw);
  Serial.print(" -> ");
  Serial.print(moisture);
  Serial.println("%");
  
  // Referensi Kalibrasi
  Serial.print("(Kering: ");
  Serial.print(SENSOR_DRY_ADC);
  Serial.print(" | Basah: ");
  Serial.print(SENSOR_WET_ADC);
  Serial.println(")");
  
  Serial.println("---");
  delay(2000); // Baca setiap 2 detik
}
