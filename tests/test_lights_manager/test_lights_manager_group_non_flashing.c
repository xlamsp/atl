#include "lights_manager.h"
#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

TEST_GROUP(NonFlashing);


/*
 * Local variables
 */
static shreg_driver_t handle = {
  .pinLatch = 2,
  .pinClock = 3,
  .pinData = 4,
  .numChips = 4
};

static uint8_t buffer[4];


/*
 * Supplementary functions
 */
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
  buffer[0] = 0b00000001;
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
  buffer[3] = 0b10000000;
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(31);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update twice after programming On changes state only once
 */
TEST(NonFlashing, UpdateTwiceAfterProgrammingOnChangesStateOnce)
{
  /* Set expectations */
  buffer[0] = 0b00000001;
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
 */
TEST(NonFlashing, UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState)
{
  /* Set expectations */
  buffer[0] = 0b00000001;
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_on(0);
  lm_update();  // change state expected

  lm_on(0);
  lm_update();  // change state not expected

  /* Verify results (implicitly via test tear down) */
}

