#include "lights_manager.h"
#include "test_lights_manager_common.h"
#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(LightsFlashing);


/*
 * Test setup and teardown
 */
TEST_SETUP(LightsFlashing)
{
  mocks_init();

  testLm_Expect_lm_init();
  lm_init();
}

TEST_TEAR_DOWN(LightsFlashing)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}


/*
 * Test cases
 */

/*
 * Programming light flashing after init does't cause changing state
 */
TEST(LightsFlashing, ProgrammingLightFlashingDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_flash(0);

  /* Verify results (implicitly via test tear down) */
}

