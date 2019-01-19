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

