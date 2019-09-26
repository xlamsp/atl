#include "lights_manager_private.h"
#include "shreg_driver.h"
#include "arduino.h"
#include <string.h>


/*******************************************************************************
 * Local variables
 ******************************************************************************/
static
shreg_driver_t handle = {
  .pinLatch = LM_PIN_LATCH,
  .pinClock = LM_PIN_CLOCK,
  .pinData  = LM_PIN_DATA,
  .numChips = LM_BUFFER_SIZE
};

static
lm_context_t lm = {
  .handle = &handle
};


/*******************************************************************************
 * Unit test helper functions
 ******************************************************************************/
#ifdef UNIT_TEST
lm_context_t *ut_lm_get_context(void)
{
  return &lm;
}
#endif /* UNIT_TEST */


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void
lm_init(void)
{
  memset(lm.buffer, 0, sizeof(lm.buffer));
  millis();
  shreg_write(lm.handle, lm.buffer);
  lm.is_buffer_changed = false;
}

void
lm_update(void)
{
  millis();
  if (lm.is_buffer_changed) {
    shreg_write(lm.handle, lm.buffer);
  }
  lm.is_buffer_changed = false;
}

void
lm_on(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  if (light > LM_LIGHT_NUMBER_MAX) {
    return;
  }

  index = light / 8;
  bit = 1 << (light % 8);

  if (lm.buffer[index] & bit) {
    return;
  }

  lm.buffer[index] |= bit;
  lm.is_buffer_changed = true;
}

void
lm_off(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  if (light > LM_LIGHT_NUMBER_MAX) {
    return;
  }

  index = light / 8;
  bit = 1 << (light % 8);

  if (!(lm.buffer[index] & bit)) {
    return;
  }

  lm.buffer[index] &= ~bit;
  lm.is_buffer_changed = true;
}

void
lm_flash(uint8_t light)
{
}

