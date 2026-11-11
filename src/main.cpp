#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// ============ GLOBAL OBJECTS ============
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// ============ GLOBAL VARIABLES ============
SystemState currentState = STATE_STANDBY;
bool isWateringActive = false;
unsigned long phaseStartTime = 0;
int moisturePercent = 0;
int sensorRawADC = 0;

// ============ FUNCTION DECLARATIONS ============
void initHardware();
void showSplashScreen();
void buzzerBeep(int duration, int count);
int readMoistureSensor();
void updateOLED();
void handleWateringLogic();

// ============ SETUP ============
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  Serial.println("=== FIKAR System Initialization ===");

  initHardware();
  showSplashScreen();
  buzzerBeep(BUZZER_SHORT_DURATION, 2); // 2x bip pendek

  Serial.println("=== FIKAR System Ready ===");
}

// ============ MAIN LOOP ============
void loop()
{
  // Baca sensor kelembapan
  moisturePercent = readMoistureSensor();

  // Logika penyiraman
  handleWateringLogic();

  // Update tampilan OLED
  updateOLED();

  delay(500); // Update setiap 0.5 detik
}

// ============ FUNCTION DEFINITIONS ============

void initHardware()
{
  // Init GPIO pins
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  digitalWrite(BUZZER_PIN, BUZZER_OFF);

  Serial.println("GPIO pins initialized");

  // Init I2C dan OLED
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN, I2C_FREQ);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("ERROR: OLED initialization FAILED!");
    while (1)
      ;
  }

  Serial.println("OLED display initialized");
}

void showSplashScreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("FIKAR SYSTEM");
  display.println("Solar Irrigation");
  display.println("v1.1.0");
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void buzzerBeep(int duration, int count)
{
  for (int i = 0; i < count; i++)
  {
    digitalWrite(BUZZER_PIN, BUZZER_ON);
    delay(duration);
    digitalWrite(BUZZER_PIN, BUZZER_OFF);
    if (i < count - 1)
      delay(300); // Jeda antar bip
  }
}

int readMoistureSensor()
{
  sensorRawADC = analogRead(SENSOR_PIN);

  // Map ADC ke persentase kelembapan (dry=3200->0%, wet=1500->100%)
  // Inversi karena ADC tinggi = kering, ADC rendah = basah
  int percent = map(sensorRawADC, SENSOR_DRY_ADC, SENSOR_WET_ADC, 0, 100);
  percent = constrain(percent, 0, 100);

  Serial.print("ADC: ");
  Serial.print(sensorRawADC);
  Serial.print(" -> Moisture: ");
  Serial.print(percent);
  Serial.println("%");

  return percent;
}

void updateOLED()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Line 1: Header
  display.setCursor(0, 0);
  display.print("FIKAR ");

  // Status sistem
  if (currentState == STATE_STANDBY)
  {
    display.println("STANDBY");
  }
  else if (currentState == STATE_PUMP_ON)
  {
    display.println("PUMP ON");
  }
  else if (currentState == STATE_PUMP_SOAKING)
  {
    display.println("SOAKING");
  }

  // Line 2: Moisture
  display.setCursor(0, 10);
  display.print("Moisture: ");
  display.print(moisturePercent);
  display.println("%");

  // Line 3: ADC raw
  display.setCursor(0, 20);
  display.print("ADC: ");
  display.println(sensorRawADC);

  display.display();
}

void handleWateringLogic()
{
  unsigned long currentTime = millis();

  switch (currentState)
  {
  case STATE_STANDBY:
    // Cek apakah perlu mulai penyiraman
    if (moisturePercent < LOWER_THRESHOLD)
    {
      Serial.println(">>> Moisture LOW - Starting watering cycle");
      buzzerBeep(BUZZER_LONG_DURATION, 1); // 1x bip panjang

      currentState = STATE_PUMP_ON;
      isWateringActive = true;
      digitalWrite(RELAY_PIN, RELAY_ON); // Nyalakan pompa
      phaseStartTime = currentTime;

      Serial.println("STATE: PUMP_ON");
    }
    break;

  case STATE_PUMP_ON:
    // Cek apakah fase pompa ON sudah selesai
    if (currentTime - phaseStartTime >= PUMP_ON_TIME)
    {
      Serial.println(">>> PUMP_ON phase complete - Entering SOAKING");

      currentState = STATE_PUMP_SOAKING;
      digitalWrite(RELAY_PIN, RELAY_OFF); // Matikan pompa
      phaseStartTime = currentTime;

      Serial.println("STATE: PUMP_SOAKING");
    }
    break;

  case STATE_PUMP_SOAKING:
    // Cek apakah fase soaking sudah selesai
    if (currentTime - phaseStartTime >= SOAK_TIME)
    {
      Serial.println(">>> SOAKING phase complete - Evaluating moisture");

      // Evaluasi kelembapan setelah soaking
      if (moisturePercent >= UPPER_THRESHOLD)
      {
        // Kelembapan cukup - hentikan siklus
        Serial.println(">>> Moisture SUFFICIENT - Stopping watering");
        buzzerBeep(BUZZER_SHORT_DURATION, 3); // 3x bip pendek

        currentState = STATE_STANDBY;
        isWateringActive = false;

        Serial.println("STATE: STANDBY");
      }
      else
      {
        // Kelembapan masih kurang - ulangi siklus
        Serial.println(">>> Moisture STILL LOW - Repeating cycle");

        currentState = STATE_PUMP_ON;
        digitalWrite(RELAY_PIN, RELAY_ON); // Nyalakan pompa lagi
        phaseStartTime = currentTime;

        Serial.println("STATE: PUMP_ON (repeat)");
      }
    }
    break;
  }
}
