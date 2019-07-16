#include "lights_manager.h"
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
uint8_t buffer[LM_BUFFER_SIZE];
static
boolean is_buffer_changed;


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void
lm_init(void)
{
  memset(buffer, 0, sizeof(buffer));
  millis();
  shreg_write(&handle, buffer);
  is_buffer_changed = false;
}

void
lm_update(void)
{
  if (is_buffer_changed) {
    shreg_write(&handle, buffer);
  }
  is_buffer_changed = false;
}

void
lm_on(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  if (light >= LM_MAX_NUMBER_OF_LIGHTS) {
    return;
  }

  index = light / 8;
  bit = 1 << (light % 8);

  if (buffer[index] & bit) {
    return;
  }

  buffer[index] |= bit;
  is_buffer_changed = true;
}

void
lm_off(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  if (light >= LM_MAX_NUMBER_OF_LIGHTS) {
    return;
  }

  index = light / 8;
  bit = 1 << (light % 8);

  if (!(buffer[index] & bit)) {
    return;
  }

  buffer[index] &= ~bit;
  is_buffer_changed = true;
}

