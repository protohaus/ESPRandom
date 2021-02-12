#include "Arduino.h"
#include "ESPRandom.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Use an old-school array to create a v4 UUID
  uint8_t uuid_array[16];
  ESPRandom::uuid4(uuid_array);
  Serial.println("UUID V4:");
  Serial.println(ESPRandom::uuidToString(uuid_array));

  // Use a bounds-checked vector to create a v4 UUID
  std::vector<uint8_t> uuid_vector = ESPRandom::uuid4();
  Serial.println("UUID V4:");
  Serial.println(ESPRandom::uuidToString(uuid_vector));

  // Create a v1 UUID with a wrong time. This may not be unique
  // See the link to update the time
  // https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
  std::vector<uint8_t> uuid_vector = ESPRandom::uuid1();
  Serial.println("UUID V1:");
  Serial.println(ESPRandom::uuidToString(uuid_vector));

  // Show error checking with invalid UUID
  // Invalid UUIDs are returned as empty strings
  std::vector<uint8_t> uuid_invalid = {1, 2, 3, 4, 5, 6};
  Serial.println("Invalid UUID v4:");
  Serial.println(ESPRandom::uuidToString(uuid_invalid));

  delay(1000);
}
