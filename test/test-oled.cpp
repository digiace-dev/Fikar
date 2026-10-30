// perpustakaan Arduino untuk mengontrol mikrokontroler
#include <Arduino.h>
// perpustakaan untuk komunikasi I2C OLED SSD1306
#include <Wire.h>
#include <Adafruit_SSD1306.h>
// impor pengaturan konstanta dari file config.h
#include "../src/config.h"

// inisialisasi objek OLED dengan lebar 128 pixel, tinggi 32 pixel, I2C address 0x3C
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup() {
  // inisialisasi komunikasi serial untuk debugging
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  Serial.println("=== TEST I2C OLED SETUP START ===");
  
  // inisialisasi I2C pada pin SDA (GPIO21) dan SCL (GPIO22) dengan frekuensi 400 kHz
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN, I2C_FREQ);
  Serial.println("I2C bus initialized");
  
  // inisialisasi display OLED pada alamat 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED initialization FAILED!");
    while (1);  // loop selamanya jika OLED gagal
  }
  Serial.println("OLED display initialized successfully");
  
  // tampilkan splash screen awal
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("FIKAR - I2C Test");
  display.println("OLED Working!");
  display.display();
  delay(2000);
  
  Serial.println("=== TEST I2C OLED SETUP DONE ===");
}

void loop() {
  // bersihkan layar display
  display.clearDisplay();
  
  // tampilkan header
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("=== I2C OLED Test ===");
  
  // tampilkan waktu runtime dalam milidetik
  display.setCursor(0, 10);
  display.print("Runtime: ");
  display.print(millis());
  display.println(" ms");
  
  // tampilkan jam loop dan status
  display.setCursor(0, 20);
  display.print("Loop Count: ");
  display.println(millis() / 1000);
  
  // update display dengan konten baru
  display.display();
  
  // print ke serial monitor untuk debugging
  Serial.print("Runtime: ");
  Serial.print(millis());
  Serial.println(" ms - OLED update OK");
  
  // tunggu 1 detik sebelum update berikutnya
  delay(1000);
}
