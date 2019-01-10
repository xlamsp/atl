#ifndef SHREG_DRIVER_H
#define SHREG_DRIVER_H

#include <stdint.h>

typedef struct {
  uint8_t pinLatch;
  uint8_t pinClock;
  uint8_t pinData;
  uint8_t numChips;
} shreg_driver_t;

void
shreg_init_input (shreg_driver_t *handle);

#endif /* SHREG_DRIVER_H */

