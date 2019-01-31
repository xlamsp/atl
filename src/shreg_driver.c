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
  digitalWrite(2, HIGH);

  /* Shift in bit from pin H */
  value |= (digitalRead(4) << 7);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin G */
  value |= (digitalRead(4) << 6);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin F */
  value |= (digitalRead(4) << 5);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin E */
  value |= (digitalRead(4) << 4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin D */
  value |= (digitalRead(4) << 3);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin C */
  value |= (digitalRead(4) << 2);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin B */
  value |= (digitalRead(4) << 1);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin A */
  value |= digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Release the latch */
  digitalWrite(2, LOW);

  /* Return result */
  buffer[0] = value;
}

