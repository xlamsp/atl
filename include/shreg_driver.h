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

void
shreg_init_output (shreg_driver_t *handle);

void
shreg_read (shreg_driver_t *handle, uint8_t *buffer);

void
shreg_write (shreg_driver_t *handle, uint8_t *buffer);

#endif /* SHREG_DRIVER_H */

