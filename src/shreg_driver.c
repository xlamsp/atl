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
shreg_read (shreg_driver_t *handle, uint8_t *buffer)
{
  uint8_t chipCount;

  /* Pull up the latch to lock registers input pins */
  digitalWrite(handle->pinLatch, HIGH);

  /* Shift in data from all chips in the chain */
  for (chipCount = 0; chipCount < handle->numChips; chipCount++) {
    buffer[chipCount] = shiftInOneChip(handle->pinData, handle->pinClock);
  }

  /* Release the latch */
  digitalWrite(handle->pinLatch, LOW);
}

