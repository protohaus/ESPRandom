#include "Arduino.h"
#include "ESPRandom.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Use an old-school array
  uint8_t uuid_array[16];
  ESPRandom::uuid(uuid_array);
  Serial.println(ESPRandom::uuidToString(uuid_array));

  // Use a bounds-checked vector
  std::vector<uint8_t> uuid_vector = ESPRandom::uuid();
  Serial.println(ESPRandom::uuidToString(uuid_vector));

  // Show error checking with invalid UUID
  // Invalid UUIDs are returned as empty strings
  std::vector<uint8_t> uuid_invalid = {1, 2, 3, 4, 5, 6};
  Serial.println(ESPRandom::uuidToString(uuid_invalid));

  delay(1000);
}
