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

