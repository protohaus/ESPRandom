#include "ESPRandom.h"

uint32_t ESPRandom::get() {
  enableRadio();
  return esp_random();
}

void ESPRandom::uuid(uint8_t* buffer) {
  for (int i = 0; i < 16; i += 4) {
    uint32_t random = get();
    memcpy(&buffer[i], &random, 4);
  }

  // Format the UUID --> version number and control bits
  buffer[6] = (buffer[6] & 0x0F) | 0x40;
  buffer[8] = (buffer[8] & 0x3F) | 0x80;
}

String ESPRandom::uuidToString(uint8_t* buffer) {
  String uuid_string;
  uuid_string.reserve(36 + 1); // Include NULL

  // Convert to HEX and break up into blocks (8, 4, 4, 4, 12)
  for (int i = 0; i < 16; i++) {
    if (i == 4 || i == 6 || i == 8 || i == 10) {
      uuid_string += "-";
    }
    uuid_string += String(buffer[i] >> 4, HEX);
    uuid_string += String(buffer[i] & 0x0F, HEX);
  }

  return uuid_string;
}

void ESPRandom::enableRadio() {
  if (WiFi.getMode() == WIFI_MODE_NULL) {
    WiFi.begin();
  }
}
