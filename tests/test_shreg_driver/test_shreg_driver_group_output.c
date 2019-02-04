#include "shreg_driver.h"
#include "mocks_arduino.h"
#include "unity_fixture.h"

TEST_GROUP(Output);

/*
 * Supplementary functions
 */
static void
expect_InitPinsForOutputChain(shreg_driver_t *handle)
{
  expect_pinMode(handle->pinLatch, OUTPUT);
  expect_pinMode(handle->pinClock, OUTPUT);
  expect_pinMode(handle->pinData, OUTPUT);

  expect_digitalWrite(handle->pinLatch, HIGH);
  expect_digitalWrite(handle->pinClock, LOW);
}

static void
expect_shiftOutOneChip(shreg_driver_t *handle, uint8_t value)
{
  int bit;

  for (bit = 7; bit >= 0; bit--) {
    expect_digitalWrite(handle->pinData, (value >> bit) & 1);
    expect_digitalWrite(handle->pinClock, HIGH);
    expect_digitalWrite(handle->pinClock, LOW);
  }
}


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
  expect_InitPinsForOutputChain(&handle);

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
  expect_InitPinsForOutputChain(&handle1);
  expect_InitPinsForOutputChain(&handle2);

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
  expect_shiftOutOneChip(&handle, write_buffer[0]);
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
  expect_shiftOutOneChip(&handle, write_buffer[0]);
  expect_digitalWrite(handle.pinLatch, HIGH); /* Latch release */

  /* Perform test */
  shreg_write(&handle, write_buffer);

  /* Verify results (implicitly via test tear down) */
}

/*
 * The driver can write arbitrary values to multiple single chip chains
 */
TEST(Output, WriteArbitraryValuesToMultipleSingleChipChains)
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
  uint8_t write_buffer1[] = { 0b00110111 };
  uint8_t write_buffer2[] = { 0b01001100 };

  /* Set expectations */
  expect_digitalWrite(handle1.pinLatch, LOW); /* Latch lock */
  expect_shiftOutOneChip(&handle1, write_buffer1[0]);
  expect_digitalWrite(handle1.pinLatch, HIGH); /* Latch release */

  expect_digitalWrite(handle2.pinLatch, LOW); /* Latch lock */
  expect_shiftOutOneChip(&handle2, write_buffer2[0]);
  expect_digitalWrite(handle2.pinLatch, HIGH); /* Latch release */

  /* Perform test */
  shreg_write(&handle1, write_buffer1);
  shreg_write(&handle2, write_buffer2);

  /* Verify results (implicitly via test tear down) */
}

