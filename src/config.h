#ifndef CONFIG_H
#define CONFIG_H

// ============ HARDWARE PINOUT ============
#define SENSOR_PIN 34            // ADC1 GPIO34 - Sensor Kelembapan
#define OLED_SDA_PIN 21          // GPIO21 - I2C SDA (OLED)
#define OLED_SCL_PIN 22          // GPIO22 - I2C SCL (OLED)
#define LED_BUILTIN_PIN 2        // GPIO2 - Built-in LED
#define RELAY_PIN 25             // GPIO25 - Modul Relay (Active-HIGH)
#define BUZZER_PIN 27            // GPIO27 - Buzzer Aktif 5V

// ============ I2C COMMUNICATION (OLED) ============
#define I2C_FREQ 400000          // I2C clock frequency (400 kHz)
#define OLED_ADDRESS 0x3C        // SSD1306 I2C address (7-bit)
#define OLED_WIDTH 128           // OLED display width (pixels)
#define OLED_HEIGHT 32           // OLED display height (pixels)

// ============ SERIAL COMMUNICATION ============
#define SERIAL_BAUD 115200       // Serial Monitor baud rate

// ============ SENSOR CALIBRATION ============
#define SENSOR_DRY_ADC 3200      // ADC value saat sensor kering (0-10%)
#define SENSOR_WET_ADC 1500      // ADC value saat sensor basah (90-100%)
#define ADC_MAX 4095             // ADC resolution 12-bit ESP32

// ============ MOISTURE THRESHOLDS (%) ============
#define LOWER_THRESHOLD 60       // Sistem aktif jika avgMoisture < 60%
#define UPPER_THRESHOLD 85       // Sistem berhenti jika avgMoisture >= 85%

// ============ PULSING PUMP TIMING (ms) ============
#define PUMP_ON_TIME 5000        // Durasi pompa menyala per siklus (5 detik)
#define SOAK_TIME 55000          // Durasi jeda peresapan air (55 detik)

// ============ BUZZER SIGNALING ============
#define BUZZER_FREQ 1000         // Frekuensi buzzer (Hz)
#define BUZZER_SHORT_DURATION 200 // Bip pendek (ms)
#define BUZZER_LONG_DURATION 500  // Bip panjang (ms)

// ============ BUZZER CONTROL LOGIC ============
#define BUZZER_ON HIGH           // Buzzer aktif-HIGH (5V mengaktifkan buzzer)
#define BUZZER_OFF LOW           // Buzzer non-aktif (0V mematikan buzzer)

// ============ SYSTEM STATE ENUM ============
enum SystemState {
  STATE_STANDBY = 0,           // Siap menunggu kondisi aktif
  STATE_PUMP_ON = 1,           // Pompa sedang menyala (5 detik)
  STATE_PUMP_SOAKING = 2       // Pompa sedang istirahat / peresapan (55 detik)
};

// ============ RELAY CONTROL LOGIC ============
#define RELAY_ON HIGH            // Relay aktif-HIGH (5V mengaktifkan pompa)
#define RELAY_OFF LOW            // Relay non-aktif (0V mematikan pompa)

#endif // CONFIG_H
