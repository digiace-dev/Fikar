// perpustakaan Arduino untuk mengontrol mikrokontroler
#include <Arduino.h>
// impor pengaturan konstanta dari file config.h
#include "../src/config.h"

void setup() {
  // inisialisasi pin digital RELAY_PIN sebagai keluaran (output)
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUD);
  Serial.println(RELAY_PIN);
}

// fungsi loop berjalan berulang kali selamanya
void loop() {
  digitalWrite(RELAY_PIN, RELAY_ON);  // aktifkan relay dengan mengatur pin ke tegangan TINGGI (HIGH) untuk menghidupkan pompa
  Serial.print(RELAY_PIN);
  Serial.print(" ");
  Serial.println(RELAY_ON);
  delay(5000);                      // tunggu 5 detik pompa menyala
  digitalWrite(RELAY_PIN, RELAY_OFF);   // matikan relay dengan mengatur pin ke tegangan RENDAH (LOW) untuk mematikan pompa
  Serial.print(RELAY_PIN);
  Serial.print(" ");
  Serial.println(RELAY_OFF);
  delay(5000);                      // tunggu 5 detik pompa off sebelum siklus berulang
}
