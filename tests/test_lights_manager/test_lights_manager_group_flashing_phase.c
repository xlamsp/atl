#include "lights_manager_private.h"
#include "test_lights_manager_common.h"
#include "mocks.h"
#include "unity_fixture.h"

/*
 * Feature: Flashing phase transition
 *
 * Define:
 * T - flashing interval;
 *
 */
TEST_GROUP(FlashingPhase);


/*
 * Local variables
 */
static lm_context_t *lm;


/*
 * Test setup and teardown
 */
TEST_SETUP(FlashingPhase)
{
  mocks_init();
  lm = ut_lm_get_context();
}

TEST_TEAR_DOWN(FlashingPhase)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}


/*
 * Test cases
 */

/*
 * Scenario: Initialization of LM resets flashing phase off;
 * Given:    The system clock is zero;
 * When:     Called init;
 * Then:     Flashing phase is off.
 */
TEST(FlashingPhase, InitResetsFashingPhaseOff)
{
  /* Set expectations */
  lm->flashing_phase = lm_flashing_phase_on; // set phase to incorrect state
  testLm_Expect_lm_init();

  /* Perform test */
  lm_init();

  /* Verify results */
  TEST_ASSERT_EQUAL(lm_flashing_phase_off, lm->flashing_phase);
}

/*
 * Scenario: Flashing phase is off when the system clock is less than T/2;
 * Given: System clock is less than T/2;
 * When: Called update;
 * Then: Flashing phase is off.
 */
TEST(FlashingPhase, FashingPhaseOffWhenClockLessThanHalfT)
{
  /* Set expectations */
  lm->flashing_phase = lm_flashing_phase_on; // set phase to incorrect state
  testLm_Expect_lm_init();
  testLm_Expect_lm_update(LM_FLASH_HALF_INTERVAL / 2);

  /* Perform test */
  lm_init();
  lm_update();

  /* Verify results */
  TEST_ASSERT_EQUAL(lm_flashing_phase_off, lm->flashing_phase);
}

