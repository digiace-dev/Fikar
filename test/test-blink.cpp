#include <Arduino.h>

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(LED_BUILTIN);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  Serial.print(LED_BUILTIN);
  Serial.print(" ");
  Serial.println(HIGH);
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  Serial.print(LED_BUILTIN);
  Serial.print(" ");
  Serial.println(LOW);
  delay(1000);                      // wait for a second
}
