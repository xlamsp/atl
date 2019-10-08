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

  testLm_Expect_lm_init(0);
  lm_init();
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

  /* Perform test - moved to test setup */

  /* Verify results (implicitly via test tear down) */
}

/*
 * Programming light Off does't cause changing state
 */
TEST(LightsOff, ProgrammingLightOffDoesNotChangeState)
{
  /* Set expectations */

  /* Perform test */
  lm_off(LM_LIGHT_NUMBER_MIN);

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn off one light with the lowest number
 */
TEST(LightsOff, TurnOffOneLightWithLowestNumber)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);   // first, turn the light on
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  testLm_ProgramLightOff(LM_LIGHT_NUMBER_MIN);  // then turn it off
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);   // first, turn the light on
  lm_update();

  lm_off(LM_LIGHT_NUMBER_MIN);  // then turn it off
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Can turn off one light with the highest number
 */
TEST(LightsOff, TurnOffOneLightWithHighestNumber)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MAX);   // first, turn the light on
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  testLm_ProgramLightOff(LM_LIGHT_NUMBER_MAX);  // then turn it off
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MAX);   // first, turn the light on
  lm_update();

  lm_off(LM_LIGHT_NUMBER_MAX);  // then turn it off
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Turning off one light doesn't turn off other lights
 */
TEST(LightsOff, TurnOffOneLightDoesNotTurnOffOthers)
{
  #define LM_LIGHT_NUMBER_ONE   (LM_LIGHT_NUMBER_MIN + 1)
  #define LM_LIGHT_NUMBER_FIVE  (LM_LIGHT_NUMBER_MIN + 5)

  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_ONE);     // first, turn the lights on
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_FIVE);
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  testLm_ProgramLightOff(LM_LIGHT_NUMBER_ONE);  // then turn one off
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_ONE);   // first, turn the lights on
  lm_on(LM_LIGHT_NUMBER_FIVE);
  lm_update();

  lm_off(LM_LIGHT_NUMBER_ONE);  // then turn one off
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Turning off light with number out of range does nothing
 */
TEST(LightsOff, TurningOffLightWithNumberOutOfRangeDoesNothing)
{
  /* Set expectations */
  testLm_Expect_lm_update(0);
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_OUT_OF_RANGE);  // first, (pretend to) turn the light on
  lm_update();

  lm_off(LM_LIGHT_NUMBER_OUT_OF_RANGE); // then (pretend to) turn it off
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

/*
 * Update after Programming Off light that is already off doesn't change state
 */
TEST(LightsOff, UpdateAfterProgrammingOffLightAlreadyOffDoesNotChangeState)
{
  /* Set expectations */
  testLm_ProgramLightOn(LM_LIGHT_NUMBER_MIN);   // first, turn the light on
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();

  testLm_ProgramLightOff(LM_LIGHT_NUMBER_MIN);  // then turn it off
  testLm_Expect_lm_update(0);
  testLm_ExpectStateChange();
  testLm_Expect_lm_update(0);

  /* Perform test */
  lm_on(LM_LIGHT_NUMBER_MIN);     // first, turn the light on
  lm_update();

  lm_off(LM_LIGHT_NUMBER_MIN);    // then turn it off
  lm_update();

  lm_off(LM_LIGHT_NUMBER_MIN);    // then turn it off again
  lm_update();

  /* Verify results (implicitly via test tear down) */
}

