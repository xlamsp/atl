#include "arduino.h"
#include "shreg_driver.h"

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
  uint8_t value = 0;

  /* Pull up the latch to lock register input pins */
  digitalWrite(handle->pinLatch, HIGH);

  /* Shift in bit from pin H */
  value |= (digitalRead(handle->pinData) << 7);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin G */
  value |= (digitalRead(handle->pinData) << 6);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin F */
  value |= (digitalRead(handle->pinData) << 5);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin E */
  value |= (digitalRead(handle->pinData) << 4);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin D */
  value |= (digitalRead(handle->pinData) << 3);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin C */
  value |= (digitalRead(handle->pinData) << 2);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin B */
  value |= (digitalRead(handle->pinData) << 1);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Shift in bit from pin A */
  value |= digitalRead(handle->pinData);
  digitalWrite(handle->pinClock, HIGH);
  digitalWrite(handle->pinClock, LOW);

  /* Release the latch */
  digitalWrite(handle->pinLatch, LOW);

  /* Return result */
  buffer[0] = value;
}

