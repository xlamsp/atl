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
  buffer[0] = 0b00000001;
  is_buffer_changed = true;
}

