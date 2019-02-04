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

/*
 * The driver can write memory buffer to the single chip chain
 */
TEST(Output, WriteSingleChipChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };
  uint8_t write_buffer[] = { 0x00 };

  /* Set expectations */
  expect_digitalWrite(handle.pinLatch, LOW); /* Latch lock */

  /* Shift out bit to pin Qh */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qg */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qf */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qe */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qd */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qc */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qb */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qa */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  expect_digitalWrite(handle.pinLatch, HIGH); /* Latch release */

  /* Perform test */
  shreg_write(&handle, write_buffer);

  /* Verify results (implicitly via test tear down) */
}

/*
 * The driver can write arbitrary value to the single chip chain
 */
TEST(Output, WriteArbitraryValueSingleChipChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };
  uint8_t write_buffer[] = { 0b10000101 };

  /* Set expectations */
  expect_digitalWrite(handle.pinLatch, LOW); /* Latch lock */

  /* Shift out bit to pin Qh */
  expect_digitalWrite(handle.pinData, HIGH);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qg */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qf */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qe */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qd */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qc */
  expect_digitalWrite(handle.pinData, HIGH);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qb */
  expect_digitalWrite(handle.pinData, LOW);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  /* Shift out bit to pin Qa */
  expect_digitalWrite(handle.pinData, HIGH);
  expect_digitalWrite(handle.pinClock, HIGH);
  expect_digitalWrite(handle.pinClock, LOW);

  expect_digitalWrite(handle.pinLatch, HIGH); /* Latch release */

  /* Perform test */
  shreg_write(&handle, write_buffer);

  /* Verify results (implicitly via test tear down) */
}

