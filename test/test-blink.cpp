// perpustakaan Arduino untuk mengontrol mikrokontroler
#include <Arduino.h>
// impor pengaturan konstanta dari file config.h
#include "../src/config.h"

void setup() {
  // inisialisasi pin digital LED_BUILTIN_PIN sebagai keluaran (output)
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUD);
  Serial.println(LED_BUILTIN_PIN);
}

// fungsi loop berjalan berulang kali selamanya
void loop() {
  digitalWrite(LED_BUILTIN_PIN, HIGH);  // nyalakan LED dengan mengatur pin ke tegangan TINGGI (HIGH)
  Serial.print(LED_BUILTIN_PIN);
  Serial.print(" ");
  Serial.println(HIGH);
  delay(500);                      // tunggu setengah detik (500 milidetik)
  digitalWrite(LED_BUILTIN_PIN, LOW);   // matikan LED dengan mengatur pin ke tegangan RENDAH (LOW)
  Serial.print(LED_BUILTIN_PIN);
  Serial.print(" ");
  Serial.println(LOW);
  delay(500);                      // tunggu setengah detik (500 milidetik)
}
