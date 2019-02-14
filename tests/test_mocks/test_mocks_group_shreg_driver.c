#include "mocks_shreg_driver.h"
#include "unity_fixture.h"

TEST_GROUP(ShregDriver);

TEST_SETUP(ShregDriver)
{
  mocks_init();
}

TEST_TEAR_DOWN(ShregDriver)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}

/*
 * mock shreg_driver shreg_init_input()
 */
TEST(ShregDriver, shreg_init_input)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };

  expect_shreg_init_input(&handle);
  shreg_init_input(&handle);
}

/*
 * mock shreg_driver shreg_init_output()
 */
TEST(ShregDriver, shreg_init_output)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };

  expect_shreg_init_output(&handle);
  shreg_init_output(&handle);
}

