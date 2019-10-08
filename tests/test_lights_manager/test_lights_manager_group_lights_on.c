#include "lights_manager.h"
#include "test_lights_manager_common.h"
#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(LightsOn);


/*
 * Test setup and teardown
 */
TEST_SETUP(LightsOn)
{
  mocks_init();

  testLm_Expect_lm_init(0);
  lm_init();
}

TEST_TEAR_DOWN(LightsOn)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}


/*
 * Test cases
 */

/*
 * Calling update if no lights programmed does't cause changing state
 */
TEST(LightsOn, LmUpdateWithoutProgrammingDoesNotChangeState)
{
  /* Set expectations */
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Programming light On does't cause changing state
 */
TEST(LightsOn, ProgrammingLightOnDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on one light with the lowest number
 */
TEST(LightsOn, TurnOnOneLightWithLowestNumber)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on one light with the highest number
 */
TEST(LightsOn, TurnOnOneLightWithHighestNumber)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MAX);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MAX);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update twice after programming On changes state only once
 */
TEST(LightsOn, UpdateTwiceAfterProgrammingOnChangesStateOnce)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_update();
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On and Init doesn't change state
 */
TEST(LightsOn, UpdateAfterProgrammingOnAndInitDoesNotChangeState)
{
  /* Set expectations */
  testLm_Expect_lm_init(0);
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_init();
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On light that is already on doesn't change state
 * (single light was turned on)
 */
TEST(LightsOn, UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState1)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_update();  // change state expected

  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_update();  // change state not expected

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn on multiple lights
 */
TEST(LightsOn, CanTurnOnMultipleLights)
{
  #define LM_LIGHT_NUMBER_FIVE  (LM_LIGHT_NUMBER_MIN + 5)

  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_FIVE);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_on(LM_LIGHT_NUMBER_FIVE);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming On light that is already on doesn't change state
 * (multiple lights were turned on)
 */
TEST(LightsOn, UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState2)
{
  #define LM_LIGHT_NUMBER_SIX   (LM_LIGHT_NUMBER_MIN + 6)

  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_SIX);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_on(LM_LIGHT_NUMBER_SIX);
  lm_update();  // change state expected

  lm_on(LM_LIGHT_NUMBER_MIN);
  lm_update();  // change state not expected

  /* Verify results (implicitly via test tear down) */
}

/*
 * Turning on light with number out of range does nothing
 */
TEST(LightsOn, TurningOnLightWithNumberOutOfRangeDoesNothing)
{
  /* Set expectations */
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_OUT_OF_RANGE);
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

