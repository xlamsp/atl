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
 * Supplementary functions
 */
static void
testLm_FlashingPhase_init(uint32_t system_clock_at_init)
{
  lm->flashing_phase = lm_flashing_phase_on; // set phase to incorrect state
  testLm_Expect_lm_init(system_clock_at_init);
  lm_init();
}

static void
testLm_FlashingPhase_update(uint32_t system_clock_at_init,
                            uint32_t system_clock_at_update,
                            lm_flashing_phase_e expected_phase)
{
  /* Set preconditions */
  testLm_FlashingPhase_init(system_clock_at_init);

  /* Set expectations */
  testLm_Expect_lm_update(system_clock_at_update);

  /* Perform test */
  lm_update();

  /* Verify results */
  TEST_ASSERT_EQUAL_MESSAGE(expected_phase, lm->flashing_phase,
    "Wrong flashing phase");
}


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

  /* Perform test */
  testLm_FlashingPhase_init(0);

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
  /* Boundary condition: time of update is zero */
  testLm_FlashingPhase_update(0,
                              0,
                              lm_flashing_phase_off);

  /* Time of update is in the middle of the flash half interval */
  testLm_FlashingPhase_update(0,
                              LM_FLASH_HALF_INTERVAL / 2,
                              lm_flashing_phase_off);

  /* Boundary condition: time of update is the last ms of flash half interval */
  testLm_FlashingPhase_update(0,
                              LM_FLASH_HALF_INTERVAL - 1,
                              lm_flashing_phase_off);
}

