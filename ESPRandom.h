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
  static String uuidToString(uint8_t buffer[16]);

  /**
   * Identical to uuidToString(uint8_t*) but with range check
   * 
   * \param buffer A 16 byte vector containing a UUID
   * \return A string containing the canonical textual representation
   */
  static String uuidToString(std::vector<uint8_t>& buffer);

 private:
  /**
   * The ESP's RNG is only real if the radio is on
   * 
   * The esp_random() function will not block but act as a pseudo-RNG if there is not entropy
   * source. This is problematic if generating UUIDs. See Arduino's built-in random function
   * 
   * \see https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/system.html#_CPPv410esp_randomv
   * \see https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
   */
  static void enableRadio();
};

#endif
