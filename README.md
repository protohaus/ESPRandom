[![MIT Licence](https://img.shields.io/github/license/protohaus/ESPRandom?style=flat-square "MIT Licence")](https://en.wikipedia.org/wiki/MIT_License)

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

### Randomness Test

| Test Name        | Rewinds | tsamples | psamples |  p-value  | Assessment |
|------------------|---------|----------|----------|-----------|------------|
| diehard_birthdays|        1|       100|       100| 0.08369138|  PASSED    |
|    diehard_operm5|        8|   1000000|       100| 0.14173840|  PASSED    |
|diehard_rank_32x32|       18|     40000|       100| 0.00000000|  FAILED    |
|  diehard_rank_6x8|       22|    100000|       100| 0.95923936|  PASSED    |
| diehard_bitstream|       24|   2097152|       100| 0.19399156|  PASSED    |
|      diehard_opso|       40|   2097152|       100| 0.00055960|   WEAK     |
|      diehard_oqso|       50|   2097152|       100| 0.55745812|  PASSED    |
|       diehard_dna|       55|   2097152|       100| 0.08215937|  PASSED    |

## Attribution

Derived the UUID v1 generation algorithm from the [stduuid](https://github.com/mariusbancila/stduuid) library.
