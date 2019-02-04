#include "arduino.h"
#include "shreg_driver.h"


/*******************************************************************************
 * Local functions
 ******************************************************************************/

static inline uint8_t
shiftInOneChip(uint8_t pinData, uint8_t pinClock)
{
  int8_t bit;
  uint8_t value = 0;

  for (bit = 7; bit >= 0; bit--) {
    value |= (digitalRead(pinData) << bit);
    digitalWrite(pinClock, HIGH);
    digitalWrite(pinClock, LOW);
  }

  return value;
}

static inline void
shiftOutOneChip(uint8_t pinData, uint8_t pinClock, uint8_t value)
{
  int8_t bit;

  for (bit = 7; bit >= 0; bit--) {
    digitalWrite(pinData, (value >> bit) & 1);
    digitalWrite(pinClock, HIGH);
    digitalWrite(pinClock, LOW);
  }
}


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void
shreg_init_input (shreg_driver_t *handle)
{
  pinMode(handle->pinLatch, OUTPUT);
  pinMode(handle->pinClock, OUTPUT);
  pinMode(handle->pinData, INPUT);

  digitalWrite(handle->pinLatch, LOW);
  digitalWrite(handle->pinClock, LOW);
}

void
shreg_init_output (shreg_driver_t *handle)
{
  pinMode(handle->pinLatch, OUTPUT);
  pinMode(handle->pinClock, OUTPUT);
  pinMode(handle->pinData, OUTPUT);

  digitalWrite(handle->pinLatch, HIGH);
  digitalWrite(handle->pinClock, LOW);
}

void
shreg_read (shreg_driver_t *handle, uint8_t *buffer)
{
  uint8_t chipCount;

  digitalWrite(handle->pinLatch, HIGH); /* Latch lock */

  for (chipCount = 0; chipCount < handle->numChips; chipCount++) {
    buffer[chipCount] = shiftInOneChip(handle->pinData, handle->pinClock);
  }

  digitalWrite(handle->pinLatch, LOW); /* Latch release */
}

void
shreg_write (shreg_driver_t *handle, uint8_t *buffer)
{
  uint8_t chipCount;

  digitalWrite(handle->pinLatch, LOW); /* Latch lock */

  for (chipCount = 0; chipCount < handle->numChips; chipCount++) {
    shiftOutOneChip(handle->pinData, handle->pinClock, buffer[chipCount]);
  }

  digitalWrite(handle->pinLatch, HIGH); /* Latch release */
}

