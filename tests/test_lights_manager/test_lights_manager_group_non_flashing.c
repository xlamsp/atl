#include "lights_manager.h"
#include "mocks_shreg_driver.h"
#include "unity_fixture.h"

TEST_GROUP(NonFlashing);


/*
 * Test setup and teardown
 */
TEST_SETUP(NonFlashing)
{
  mocks_init();
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
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 4
  };
  uint8_t buffer[] = { 0, 0, 0, 0 };

  /* Set expectations */
  expect_shreg_write(&handle, buffer);

  /* Perform test */
  lm_init();

  /* Verify results (implicitly via test tear down) */
}

