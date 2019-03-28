#include "lights_manager.h"
#include "test_lights_manager_common.h"
#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

TEST_GROUP(LightsOff);

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
 * Test setup and teardown
 */
TEST_SETUP(LightsOff)
{
  mocks_init();
}

TEST_TEAR_DOWN(LightsOff)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}


/*
 * Test cases
 */

/*
 * Initialization of LM turns all the lights off
 */
TEST(LightsOff, LmInitTurnsAllLightsOff)
{
  /* Set expectations - moved to test setup */
  testLm_Expect_lm_init();

  /* Perform test - moved to test setup */
  lm_init();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Programming light Off does't cause changing state
 */
TEST(LightsOff, ProgrammingLightOffDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_off(0);

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn off one light with the lowest number
 */
TEST(LightsOff, TurnOffOneLightWithLowestNumber)
{
  /* Set expectations */
  testLm_Expect_lm_init();

  testLm_ProgramLightOn(0);           // first, turn the light on
  testLm_ExpectStateChange();

  memset(buffer, 0, sizeof(buffer));  // then turn it off
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_init();

  lm_on(0);     // first, turn the light on
  lm_update();

  lm_off(0);    // then turn it off
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

