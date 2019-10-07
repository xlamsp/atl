#ifndef LIGHTS_MANAGER_PRIVATE_H
#define LIGHTS_MANAGER_PRIVATE_H

#include "lights_manager.h"
#include "shreg_driver.h"
#include "arduino.h"

typedef enum {
  lm_flashing_phase_off,
  lm_flashing_phase_on
} lm_flashing_phase_e;

typedef struct {
  shreg_driver_t *handle;

  uint8_t buffer[LM_BUFFER_SIZE];
  boolean is_buffer_changed;
  lm_flashing_phase_e flashing_phase;
} lm_context_t;


/*******************************************************************************
 * Unit test helper functions
 ******************************************************************************/
#ifdef UNIT_TEST
lm_context_t *ut_lm_get_context (void);
#endif /* UNIT_TEST */


#endif /* LIGHTS_MANAGER_PRIVATE_H */

