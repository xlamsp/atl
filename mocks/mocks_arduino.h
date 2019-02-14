#ifndef MOCKS_ARDUINO_H
#define MOCKS_ARDUINO_H

#include "mocks.h"
#include "arduino.h"

enum {
  mock_id_pinMode = mocks_id_offset_arduino,
  mock_id_digitalWrite,
  mock_id_digitalRead,
  mock_id_millis,
};

void
expect_pinMode(uint8_t pin, uint8_t mode);

void
expect_digitalWrite(uint8_t pin, uint8_t val);

void
expect_digitalRead(int16_t ret, uint8_t pin);

void
expect_millis(uint32_t ret);

#endif /* MOCKS_ARDUINO_H */

