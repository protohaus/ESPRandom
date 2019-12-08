#include "Arduino.h"
#include "ESPRandom.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(ESPRandom::get());
  delay(1000);
}
