#include <Arduino.h>
#include "../src/config.h"

void setup() {
  // initialize digital pin LED_BUILTIN_PIN as an output.
  pinMode(LED_BUILTIN_PIN, OUTPUT);
  Serial.begin(SERIAL_BAUD);
  Serial.println(LED_BUILTIN_PIN);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN_PIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  Serial.print(LED_BUILTIN_PIN);
  Serial.print(" ");
  Serial.println(HIGH);
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN_PIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  Serial.print(LED_BUILTIN_PIN);
  Serial.print(" ");
  Serial.println(LOW);
  delay(500);                      // wait for a second
}
