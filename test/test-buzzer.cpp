// perpustakaan Arduino untuk mengontrol mikrokontroler
#include <Arduino.h>
// impor pengaturan konstanta dari file config.h
#include "../src/config.h"

void setup() {
  // inisialisasi pin digital BUZZER_PIN sebagai keluaran (output)
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUD);
  Serial.println(BUZZER_PIN);
}

// fungsi loop berjalan berulang kali selamanya
void loop() {
  // nyalakan buzzer selama 200 ms (bip pendek) dengan mengatur pin ke tegangan TINGGI (HIGH)
  digitalWrite(BUZZER_PIN, BUZZER_ON);
  Serial.print(BUZZER_PIN);
  Serial.println(" bip pendek");
  delay(BUZZER_SHORT_DURATION);  // tunggu 200 milidetik
  
  // matikan buzzer dengan mengatur pin ke tegangan RENDAH (LOW)
  digitalWrite(BUZZER_PIN, BUZZER_OFF);
  Serial.println("buzzer mati");
  delay(1000);  // tunggu 1 detik sebelum bip berikutnya
  
  // nyalakan buzzer selama 500 ms (bip panjang) dengan mengatur pin ke tegangan TINGGI (HIGH)
  digitalWrite(BUZZER_PIN, BUZZER_ON);
  Serial.print(BUZZER_PIN);
  Serial.println(" bip panjang");
  delay(BUZZER_LONG_DURATION);  // tunggu 500 milidetik
  
  // matikan buzzer dengan mengatur pin ke tegangan RENDAH (LOW)
  digitalWrite(BUZZER_PIN, BUZZER_OFF);
  Serial.println("buzzer mati");
  delay(1000);  // tunggu 1 detik sebelum siklus berulang
}
