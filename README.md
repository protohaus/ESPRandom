# ESPRandom
Generate random numbers and UUIDs on the ESP8266 and ESP32 using the hardware RNG

## Examples

### Get a Guaranteed Random Number

``` cpp
#include "Arduino.h"
#include "ESPRandom.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(ESPRandom::get());
  delay(1000);
}
```

### Get a Very Unique UUID

``` cpp
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
```

## Sunny Conditions for Random Numbers

For random numbers to be generated, the radio (WiFi or Bluetooth) have to be active. Therefore, when getting a random number (or UUID) it will check if WiFi is active and activate it (in station mode) if this is not the case.

Another reason for creating this library is that the alternatives are covered in copy-left licences which significantly restrict their use.
