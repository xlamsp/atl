#ifndef LIGHTS_MANAGER_PRIVATE_H
#define LIGHTS_MANAGER_PRIVATE_H

#include "lights_manager.h"
#include "shreg_driver.h"
#include "arduino.h"


typedef struct {
  shreg_driver_t *handle;

  uint8_t buffer[LM_BUFFER_SIZE];
  boolean is_buffer_changed;
} lm_context_t;

#endif /* LIGHTS_MANAGER_PRIVATE_H */

