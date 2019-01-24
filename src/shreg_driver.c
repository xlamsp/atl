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
  /* Pull up the latch to lock register input pins */
  digitalWrite(2, HIGH);

  /* Shift in bit from pin H */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin G */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin F */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin E */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin D */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin C */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin B */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Shift in bit from pin A */
  digitalRead(4);
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  /* Release the latch */
  digitalWrite(2, LOW);

  /* Return result */
  buffer[0] = 0;
}

