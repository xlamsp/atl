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
testLm_FlashingPhase_expect_init(uint32_t system_clock_at_init)
{
  lm->flashing_phase = lm_flashing_phase_on; // set phase to incorrect state
  testLm_Expect_lm_init(system_clock_at_init);
  lm_init();
}

static void
testLm_FlashingPhase_expect_update(uint32_t system_clock_at_update)
{
  testLm_Expect_lm_update(system_clock_at_update);
  lm_update();
}

static void
testLm_FlashingPhase_init(uint32_t system_clock_at_init)
{
  testLm_FlashingPhase_expect_init(system_clock_at_init);

  if (lm->flashing_phase != lm_flashing_phase_off) {
    char message[128];
    sprintf(message, "Wrong flashing phase system_clock_at_init=%u",
      system_clock_at_init);
    TEST_ASSERT_EQUAL_MESSAGE(lm_flashing_phase_off, lm->flashing_phase,
      message);
  }
}

static void
testLm_FlashingPhase_init_and_update(
  uint32_t system_clock_at_init,
  uint32_t system_clock_at_update,
  lm_flashing_phase_e expected_phase)
{
  testLm_FlashingPhase_expect_init(system_clock_at_init);
  testLm_FlashingPhase_expect_update(system_clock_at_update);

  if (lm->flashing_phase != expected_phase) {
    char message[128];
    sprintf(message, "Wrong flashing phase system_clock_at_update=%u",
      system_clock_at_update);
    TEST_ASSERT_EQUAL_MESSAGE(expected_phase, lm->flashing_phase,
      message);
  }
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
 *
 * This is covered by:
 * TEST(FlashingPhase, InitResetsFashingPhaseOffAtAnyTime)
 * when N == 0
 */

/*
 * Scenario: Flashing phase is off when the system clock is less than T/2;
 * Given: System clock is less than T/2;
 * When: Called update;
 * Then: Flashing phase is off.
 *
 * This is covered by:
 * TEST(FlashingPhase, FashingPhaseOffWhenClockGtOrEqNxTButLessNxHalfT)
 * when N == 0
 */

/*
 * Scenario: Flashing phase is on when the system clock is greater than or
 *           equal to T/2 but less than T;
 * Given: System clock is greater than or equal to T/2 but less than T;
 * When: Called update;
 * Then: Flashing phase is on.
 *
 * This is covered by:
 * TEST(FlashingPhase, FashingPhaseOnWhenClockGtOrEqNplus05xTButLessNplis1xT)
 * when N == 0
 */

/*
 * Scenario: Flashing phase is off when the system clock is greater than or
 *           equal to N * T but less than (N + 1/2) * T;
 * Given: System clock is greater than or equal to N * T
 *        but less than (N + 1/2) * T;
 * When: Called update;
 * Then: Flashing phase is off.
 */
TEST(FlashingPhase, FashingPhaseOffWhenClockGtOrEqNxTButLessNxHalfT)
{
  uint32_t N;

  static const
  uint32_t system_clock_at_init = 0;
  uint32_t system_clock_at_update;

  for (N = 0; N < 3; N++) {
    /* Test lower bound */
    system_clock_at_update = LM_FLASH_INTERVAL * N;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_off);

    /* Test middle of the interval */
    system_clock_at_update = LM_FLASH_INTERVAL * N + LM_FLASH_HALF_INTERVAL / 2;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_off);

    /* Test upper bound */
    system_clock_at_update = LM_FLASH_INTERVAL * N + LM_FLASH_HALF_INTERVAL - 1;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_off);
  }
}

/*
 * Scenario: Flashing phase is on when the system clock is greater than or
 *           equal to (N + 1/2) * T but less than (N + 1) * T;
 * Given: System clock is greater than or equal to (N + 1/2) * T
 *        but less than (N + 1) * T;
 * When: Called update;
 * Then: Flashing phase is on.
 */
TEST(FlashingPhase, FashingPhaseOnWhenClockGtOrEqNplus05xTButLessNplis1xT)
{
  uint32_t N;

  static const
  uint32_t system_clock_at_init = 0;
  uint32_t system_clock_at_update;

  for (N = 0; N < 3; N++) {
    /* Test lower bound */
    system_clock_at_update = LM_FLASH_INTERVAL * N + LM_FLASH_HALF_INTERVAL;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_on);

    /* Test middle of the interval */
    system_clock_at_update = LM_FLASH_INTERVAL * N +
                             3 * LM_FLASH_HALF_INTERVAL / 2;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_on);

    /* Test upper bound */
    system_clock_at_update = LM_FLASH_INTERVAL * N + LM_FLASH_INTERVAL - 1;
    testLm_FlashingPhase_init_and_update(
      system_clock_at_init,
      system_clock_at_update,
      lm_flashing_phase_on);
  }
}

/*
 * Scenario: Initialization of LM resets flashing phase off
 *           regardless of the current system time;
 * Given:    System clock is C != 0;
 * When:     Called init;
 * Then:     Flashing phase is off.
 */
TEST(FlashingPhase, InitResetsFashingPhaseOffAtAnyTime)
{
  /* Set expectations */
  uint32_t N;
  uint32_t half_interval;
  uint32_t system_clock_at_init;

  for (N = 0; N < 3; N++) {
    for (half_interval = 0;
         half_interval <= LM_FLASH_HALF_INTERVAL;
         half_interval += LM_FLASH_HALF_INTERVAL) {

      /* Test lower bound */
      system_clock_at_init = half_interval + LM_FLASH_INTERVAL * N;
      testLm_FlashingPhase_init(system_clock_at_init);

      /* Test middle of the interval */
      system_clock_at_init = half_interval + LM_FLASH_INTERVAL * N +
        LM_FLASH_HALF_INTERVAL / 2;
      testLm_FlashingPhase_init(system_clock_at_init);

      /* Test upper bound */
      system_clock_at_init = half_interval + LM_FLASH_INTERVAL * N +
        LM_FLASH_HALF_INTERVAL - 1;
      testLm_FlashingPhase_init(system_clock_at_init);
    }
  }
}

