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
  digitalWrite(handle->pinLatch, LOW); /* Latch lock */

  /* Shift out bit to pin Qh */
  digitalWrite(handle->pinData, (buffer[0] >> 7) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qg */
  digitalWrite(handle->pinData, (buffer[0] >> 6) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qf */
  digitalWrite(handle->pinData, (buffer[0] >> 5) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qe */
  digitalWrite(handle->pinData, (buffer[0] >> 4) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qd */
  digitalWrite(handle->pinData, (buffer[0] >> 3) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qc */
  digitalWrite(handle->pinData, (buffer[0] >> 2) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qb */
  digitalWrite(handle->pinData, (buffer[0] >> 1) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift out bit to pin Qa */
  digitalWrite(handle->pinData, (buffer[0] >> 0) & 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  digitalWrite(handle->pinLatch, HIGH); /* Latch release */
}

