#include "arduino.h"
#include "shreg_driver.h"

void
shreg_init_input (shreg_driver_t *handle)
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

