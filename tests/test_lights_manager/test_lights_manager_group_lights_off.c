#include "lights_manager.h"
#include "test_lights_manager_common.h"
#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(LightsOff);


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

