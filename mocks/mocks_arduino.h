#ifndef MOCKS_ARDUINO_H
#define MOCKS_ARDUINO_H

#include "mocks.h"
#include "arduino.h"

enum {
  mock_id_pinMode,
  mock_id_digitalWrite,
  mock_id_digitalRead,
};

void
expect_pinMode(uint8_t pin, uint8_t mode);

void
expect_digitalWrite(uint8_t pin, uint8_t val);

void
expect_digitalRead(int16_t ret, uint8_t pin);

#endif /* MOCKS_ARDUINO_H */

