#include "lights_manager.h"
#include "arduino.h"
#include <string.h>


/*******************************************************************************
 * Local variables
 ******************************************************************************/
static
shreg_driver_t handle = {
  .pinLatch = 2,
  .pinClock = 3,
  .pinData = 4,
  .numChips = 4
};

static
uint8_t buffer[4];
static
boolean is_buffer_changed;


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void
lm_init(void)
{
  memset(buffer, 0, sizeof(buffer));
  shreg_write(&handle, buffer);
}

void
lm_update(void)
{
  if (is_buffer_changed) {
    shreg_write(&handle, buffer);
  }
}

void
lm_on(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  index = light / 8;
  bit = 1 << (light % 8);

  buffer[index] = bit;
  is_buffer_changed = true;
}

