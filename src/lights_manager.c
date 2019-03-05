#include "lights_manager.h"


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

static uint8_t buffer[4];


/*******************************************************************************
 * Public functions
 ******************************************************************************/

void
lm_init(void)
{
  shreg_write(&handle, buffer);
}

void
lm_update(void)
{
}

