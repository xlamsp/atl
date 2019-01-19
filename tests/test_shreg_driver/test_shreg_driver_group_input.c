#include "shreg_driver.h"
#include "mocks_arduino.h"
#include "unity_fixture.h"

TEST_GROUP(Input);

TEST_SETUP(Input)
{
  mocks_init();
}

TEST_TEAR_DOWN(Input)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}

/*
 * The driver can initialize controller's pins to work with input registers
 */
TEST(Input, InitPinsSingleChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };

  expect_pinMode(handle.pinLatch, OUTPUT);
  expect_pinMode(handle.pinClock, OUTPUT);
  expect_pinMode(handle.pinData, INPUT);
  expect_digitalWrite(handle.pinLatch, LOW);
  expect_digitalWrite(handle.pinClock, LOW);

  shreg_init_input(&handle);
}

/*
 * The driver can initialize multiple input chains with different parameters
 */
TEST(Input, InitPinsMultipleChains)
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

  expect_pinMode(handle1.pinLatch, OUTPUT);
  expect_pinMode(handle1.pinClock, OUTPUT);
  expect_pinMode(handle1.pinData, INPUT);
  expect_digitalWrite(handle1.pinLatch, LOW);
  expect_digitalWrite(handle1.pinClock, LOW);

  expect_pinMode(handle2.pinLatch, OUTPUT);
  expect_pinMode(handle2.pinClock, OUTPUT);
  expect_pinMode(handle2.pinData, INPUT);
  expect_digitalWrite(handle2.pinLatch, LOW);
  expect_digitalWrite(handle2.pinClock, LOW);

  shreg_init_input(&handle1);
  shreg_init_input(&handle2);
}

