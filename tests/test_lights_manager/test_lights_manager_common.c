#include "lights_manager.h"
#include "mocks_arduino.h"
#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

/*
 * Local variables
 */
static shreg_driver_t handle = {
  .pinLatch = LM_PIN_LATCH,
  .pinClock = LM_PIN_CLOCK,
  .pinData  = LM_PIN_DATA,
  .numChips = LM_BUFFER_SIZE
};

static uint8_t buffer[LM_BUFFER_SIZE];


/*
 * Supplementary functions
 */
void
testLm_ProgramLightOn(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  TEST_ASSERT_LESS_OR_EQUAL_UINT8_MESSAGE(LM_LIGHT_NUMBER_MAX, light,
    "Invalid light number");

  index = light / 8;
  bit = 1 << (light % 8);

  buffer[index] |= bit;
}

void
testLm_ProgramLightOff(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  TEST_ASSERT_LESS_OR_EQUAL_UINT8_MESSAGE(LM_LIGHT_NUMBER_MAX, light,
    "Invalid light number");

  index = light / 8;
  bit = ~(1 << (light % 8));

  buffer[index] &= bit;
}

void
testLm_ExpectStateChange(void)
{
  expect_shreg_write(&handle, buffer);
}

void
testLm_Expect_lm_init(uint32_t system_clock_at_init)
{
  memset(buffer, 0, sizeof(buffer));
  expect_millis(system_clock_at_init);
  testLm_ExpectStateChange();
}

void
testLm_Expect_lm_update(uint32_t system_clock_at_update)
{
  expect_millis(system_clock_at_update);
}

