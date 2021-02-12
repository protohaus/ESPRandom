#include "ESPRandom.h"

uint32_t ESPRandom::get() {
  enableRadio();
  return esp_random();
}

void ESPRandom::uuid(uint8_t* buffer) { uuid4(buffer); }

void ESPRandom::uuid1(uint8_t* buffer) {
  // Get the number of 100ns periods since October 15, 1582 at midnight UTC
  auto start = std::chrono::system_clock::from_time_t(time_t(-12219292800));
  auto diff = std::chrono::system_clock::now() - start;
  int64_t ns =
      std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
  int64_t timestamp = ns / 100;

  // Use an incrementing sequence to augment "low" resolution (µs) clocks
  uint16_t clock_sequence = clock_sequence_++;
  clock_sequence &= 0x3FFF;

  uint8_t* p_timestamp = reinterpret_cast<uint8_t*>(&timestamp);
  p_timestamp[0] &= 0x0F;

  memcpy(&buffer[0], p_timestamp + 4, 4);
  memcpy(&buffer[4], p_timestamp + 2, 2);
  memcpy(&buffer[6], p_timestamp, 2);

  memcpy(&buffer[8], reinterpret_cast<uint8_t*>(&clock_sequence), 2);

  // Variant must be 0b10xxxxxx
  buffer[8] &= 0xBF;
  buffer[8] |= 0x80;

  // Version must be 0b0001xxxx
  buffer[6] &= 0x5F;
  buffer[6] |= 0x10;

  // Get the MAC address
  uint8_t mac_address[6];
  WiFi.macAddress(mac_address);
  memcpy(&buffer[10], mac_address, 6);
}

void ESPRandom::uuid4(uint8_t* buffer) {
  for (int i = 0; i < 16; i += 4) {
    uint32_t random = get();
    memcpy(&buffer[i], &random, 4);
  }

  // Format the UUID --> version number and control bits
  buffer[6] = (buffer[6] & 0x0F) | 0x40;
  buffer[8] = (buffer[8] & 0x3F) | 0x80;
}

std::vector<uint8_t> ESPRandom::uuid() { return uuid4(); }

std::vector<uint8_t> ESPRandom::uuid1() {
  std::vector<uint8_t> buffer = std::vector<uint8_t>(16);
  ESPRandom::uuid1(&buffer.front());
  return buffer;
}

std::vector<uint8_t> ESPRandom::uuid4() {
  std::vector<uint8_t> buffer = std::vector<uint8_t>(16);
  ESPRandom::uuid(&buffer.front());
  return buffer;
}

String ESPRandom::uuidToString(const uint8_t* buffer) {
  String uuid_string;
  uuid_string.reserve(36 + 1);  // Include NULL

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

String ESPRandom::uuidToString(const std::vector<uint8_t>& buffer) {
  if (buffer.size() != 16) {
    return String();
  }

  return uuidToString(&buffer.front());
}

bool ESPRandom::isValidV4Uuid(const uint8_t* buffer) {
  // The 13th hex has to be 4
  if (buffer[6] >> 4 != 0x4) {
    return false;
  }

  // The 17th hex has to by 0x8, 0x9, 0xA or 0xB
  uint8_t hex17 = buffer[8] >> 4;
  if (hex17 != 0x8 && hex17 != 0x9 && hex17 != 0xA && hex17 != 0xB) {
    return false;
  }

  return true;
}

bool ESPRandom::isValidV4Uuid(const std::vector<uint8_t>& buffer) {
  if (buffer.size() == 16) {
    return isValidV4Uuid(&buffer.front());
  } else {
    return false;
  }
}

void ESPRandom::enableRadio() {
  if (WiFi.getMode() == WIFI_MODE_NULL) {
    WiFi.begin();
  }
}

uint16_t ESPRandom::clock_sequence_ = {};
