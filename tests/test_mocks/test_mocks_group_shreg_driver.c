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

/*
 * mock shreg_driver shreg_read()
 */
TEST(ShregDriver, shreg_read)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 2
  };

  uint8_t expected_buffer[] = { 0b10000100, 0b00010011 };
  uint8_t read_buffer[] = { 0, 0 };

  expect_shreg_read(&handle, expected_buffer);
  shreg_read(&handle, read_buffer);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    expected_buffer, read_buffer, handle.numChips,
    "Incorrect data read from the chain");
}

/*
 * mock shreg_driver shreg_write()
 */
TEST(ShregDriver, shreg_write)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 2
  };

  uint8_t write_buffer[] = { 0b10000100, 0b00010011 };

  expect_shreg_write(&handle, write_buffer);
  shreg_write(&handle, write_buffer);
}

