#include "shreg_driver.h"
#include "mocks_arduino.h"
#include "unity_fixture.h"

TEST_GROUP(Output);


/*
 * Test setup and teardown
 */
TEST_SETUP(Output)
{
  mocks_init();
}

TEST_TEAR_DOWN(Output)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}


/*
 * Test cases
 */

/*
 * The driver can initialize controller's pins to work with output registers
 */
TEST(Output, InitPinsSingleChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };

  /* Set expectations */
  expect_pinMode(handle.pinLatch, OUTPUT);
  expect_pinMode(handle.pinClock, OUTPUT);
  expect_pinMode(handle.pinData, OUTPUT);

  expect_digitalWrite(handle.pinLatch, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Perform test */
  shreg_init_output(&handle);

  /* Verify results (implicitly via test tear down) */
}

/*
 * The driver can initialize multiple output chains with different parameters
 */
TEST(Output, InitPinsMultipleChains)
{
  shreg_driver_t handle1 = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };
  shreg_driver_t handle2 = {
    .pinLatch = 5,
    .pinClock = 6,
    .pinData = 7,
    .numChips = 1
  };

  /* Set expectations */
  expect_pinMode(handle1.pinLatch, OUTPUT);
  expect_pinMode(handle1.pinClock, OUTPUT);
  expect_pinMode(handle1.pinData, OUTPUT);

  expect_digitalWrite(handle1.pinLatch, HIGH);
  expect_digitalWrite(handle1.pinClock, LOW);

  expect_pinMode(handle2.pinLatch, OUTPUT);
  expect_pinMode(handle2.pinClock, OUTPUT);
  expect_pinMode(handle2.pinData, OUTPUT);

  expect_digitalWrite(handle2.pinLatch, HIGH);
  expect_digitalWrite(handle2.pinClock, LOW);

  /* Perform test */
  shreg_init_output(&handle1);
  shreg_init_output(&handle2);

  /* Verify results (implicitly via test tear down) */
}

