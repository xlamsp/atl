#include "lights_manager.h"
#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

TEST_GROUP(NonFlashing);


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
static void
bufferLightOn(uint8_t light)
{
  uint8_t index;
  uint8_t bit;

  if (light >= LM_MAX_NUMBER_OF_LIGHTS) {
    return;
  }

  index = light / 8;
  bit = 1 << (light % 8);

  buffer[index] |= bit;
}

static void
setExpectations_lm_init(void)
{
  memset(buffer, 0, sizeof(buffer));
  expect_shreg_write(&handle, buffer);
}


/*
 * Test setup and teardown
 */
TEST_SETUP(NonFlashing)
{
  mocks_init();

  setExpectations_lm_init();
  lm_init();
}

TEST_TEAR_DOWN(NonFlashing)
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
TEST(NonFlashing, LmInitTurnsAllLightsOff)
{
  /* Set expectations - moved to test setup */

  /* Perform test - moved to test setup */

  /* Verify results (implicitly via test tear down) */
}

/*
 * Calling update if no lights programmed does't cause changing state
 */
TEST(NonFlashing, LmUpdateWithoutProgrammingDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Programming light On does't cause changing state
 */
TEST(NonFlashing, ProgrammingLightOnDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_on(0);

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on one light with the lowest number
 */
TEST(NonFlashing, TurnOnOneLightWithLowestNumber)
{
  /* Set expectations */
  bufferLightOn(0);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on one light with the highest number
 */
TEST(NonFlashing, TurnOnOneLightWithHighestNumber)
{
  /* Set expectations */
  bufferLightOn(LM_MAX_NUMBER_OF_LIGHTS - 1);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(LM_MAX_NUMBER_OF_LIGHTS - 1);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update twice after programming On changes state only once
 */
TEST(NonFlashing, UpdateTwiceAfterProgrammingOnChangesStateOnce)
{
  /* Set expectations */
  bufferLightOn(0);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_update();
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On and Init doesn't change state
 */
TEST(NonFlashing, UpdateAfterProgrammingOnAndInitDoesNotChangeState)
{
  /* Set expectations */
  setExpectations_lm_init();

  /* Perform test */
  lm_on(0);
  lm_init();
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On light that is already on doesn't change state
 * (single light was turned on)
 */
TEST(NonFlashing, UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState1)
{
  /* Set expectations */
  bufferLightOn(0);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_update();  // change state expected

  lm_on(0);
  lm_update();  // change state not expected

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on multiple lights
 */
TEST(NonFlashing, CanTurnOnMultipleLights)
{
  /* Set expectations */
  bufferLightOn(0);
  bufferLightOn(5);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_on(5);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On light that is already on doesn't change state
 * (multiple lights were turned on)
 */
TEST(NonFlashing, UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState2)
{
  /* Set expectations */
  bufferLightOn(0);
  bufferLightOn(6);
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_on(6);
  lm_update();  // change state expected

  lm_on(0);
  lm_update();  // change state not expected

  /* Verify results (implicitly via test tear down) */
}

/*
 * Turning on light with number out of range does nothing
 */
TEST(NonFlashing, TurningOnLightWithNumberOutOfRangeDoesNothing)
{
  /* Set expectations */

  /* Perform test */
  lm_on(LM_MAX_NUMBER_OF_LIGHTS);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

