#ifndef MOCKS_ARDUINO_H
#define MOCKS_ARDUINO_H

#include "mocks.h"
#include "arduino.h"

enum {
  mock_id_pinMode,
};

void
expect_pinMode(uint8_t pin, uint8_t mode);

#endif /* MOCKS_ARDUINO_H */

