/**
 * ESPRandom: Generate random numbers and UUIDs on the ESP8266 and ESP32
 */

#ifndef ESPRandom_h
#define ESPRandom_h

#include "Arduino.h"
#include "WiFi.h"

class ESPRandom {
 public:
  /**
   * Generate a random number
   * 
   * \return Returns a 32 bit random number
   */
  static uint32_t get();

  /**
   * Generate a UUID in the buffer provided
   * 
   * \param buffer A 16 byte array where the UUID will be saved in
   */
  static void uuid(uint8_t buffer[16]);

  /**
   * Generate a UUID 
   * 
   * \return A vector with the generated UUID
   */
  static std::vector<uint8_t> uuid();

  /**
   * Convert a binary UUID into a String
   * 
   * \param buffer A 16 byte array containing a UUID
   * \return A string containing the canonical textual representation, empty on error
   */
  static String uuidToString(const uint8_t buffer[16]);

  /**
   * Identical to uuidToString(uint8_t*) but with range check
   * 
   * \param buffer A 16 byte vector containing a UUID
   * \return A string containing the canonical textual representation
   */
  static String uuidToString(const std::vector<uint8_t>& buffer);

  /**
   * Checks if the UUID is a valid v4 UUID
   * 
   * xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx where x is any hexadecimal digit and y is one of 8, 9, A, or B
   * 
   * \param buffer A 16 byte buffer containing the UUID
   * \return True if it is valid
   */
  static bool isValidV4Uuid(const uint8_t* buffer);

  /**
   * Checks if the UUID is a valid v4 UUID
   * 
   * xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx where x is any hexadecimal digit and y is one of 8, 9, A, or B
   * 
   * \param buffer A vector containing the UUID
   * \return True if it is valid
   */
  static bool isValidV4Uuid(const std::vector<uint8_t>& buffer);

 private:
  /**
   * The ESP's RNG only receives entropy when the WiFi / Bluetooth radio is on
   * 
   * The esp_random() function will not block but act as a pseudo-RNG if there is not entropy
   * source. Tests have shown that even without the radio, dieharder checks will confirm the
   * generated numbers as random. This is problematic if generating UUIDs. Arduino's built-in
   * random function is purely a pseudo-RNG and will generate the same numbers upon restart.
   * 
   * \see https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/system.html#_CPPv410esp_randomv
   * \see https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
   */
  static void enableRadio();
};

#endif
