#include "Arduino.h"
#include "ESPRandom.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint8_t uuid[16];
  ESPRandom::uuid(uuid);
  Serial.println(ESPRandom::uuidToString(uuid));
  delay(1000);
}
