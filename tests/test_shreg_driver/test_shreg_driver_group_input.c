#include "shreg_driver.h"
#include "mocks_arduino.h"
#include "unity_fixture.h"

TEST_GROUP(Input);

/*
 * Supplementary functions
 */
static void
expect_InitPinsForInputChain(shreg_driver_t *handle)
{
  expect_pinMode(handle->pinLatch, OUTPUT);
  expect_pinMode(handle->pinClock, OUTPUT);
  expect_pinMode(handle->pinData, INPUT);
  expect_digitalWrite(handle->pinLatch, LOW);
  expect_digitalWrite(handle->pinClock, LOW);
}

static void
expect_shiftInOneChip(shreg_driver_t *handle, uint8_t value)
{
  int i;

  for (i = 7; i >= 0; i--) {
    expect_digitalRead((value >> i) & 1, handle->pinData);
    expect_digitalWrite(handle->pinClock, HIGH);
    expect_digitalWrite(handle->pinClock, LOW);
  }
}


/*
 * Test setup and teardown
 */
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
 * Test cases
 */

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

  expect_InitPinsForInputChain(&handle);

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

  expect_InitPinsForInputChain(&handle1);
  expect_InitPinsForInputChain(&handle2);

  shreg_init_input(&handle1);
  shreg_init_input(&handle2);
}

/*
 * The driver can read single chip chain into the memory buffer
 */
TEST(Input, ReadSingleChipChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };
  uint8_t expected_buffer[] = { 0 };
  uint8_t read_buffer[] = { 0xa5 };

  /* Pull up the latch to lock register input pins */
  expect_digitalWrite(handle.pinLatch, HIGH);

  expect_shiftInOneChip(&handle, expected_buffer[0]);

  /* Release the latch */
  expect_digitalWrite(handle.pinLatch, LOW);

  shreg_read(&handle, read_buffer);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    expected_buffer, read_buffer, handle.numChips,
    "Incorrect data read from the chain");
}

/*
 * The driver can read arbitrary value from the single chip chain
 */
TEST(Input, ReadArbitraryValueSingleChipChain)
{
  shreg_driver_t handle = {
    .pinLatch = 2,
    .pinClock = 3,
    .pinData = 4,
    .numChips = 1
  };
  uint8_t expected_buffer[] = { 0x85 };
  uint8_t read_buffer[] = { 0x00 };

  /* Pull up the latch to lock register input pins */
  expect_digitalWrite(handle.pinLatch, HIGH);

  expect_shiftInOneChip(&handle, expected_buffer[0]);

  /* Release the latch */
  expect_digitalWrite(handle.pinLatch, LOW);

  shreg_read(&handle, read_buffer);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    expected_buffer, read_buffer, handle.numChips,
    "Incorrect data read from the chain");
}

/*
 * The driver can read arbitrary values from multiple single chip chains
 */
TEST(Input, ReadArbitraryValuesFromMultipleSingleChipChains)
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
  uint8_t expected_buffer1[] = { 0x37 };
  uint8_t expected_buffer2[] = { 0x4c };
  uint8_t read_buffer[] = { 0x00 };

  /* Set expectations for chain 1 */
  expect_digitalWrite(handle1.pinLatch, HIGH);
  expect_shiftInOneChip(&handle1, expected_buffer1[0]);
  expect_digitalWrite(handle1.pinLatch, LOW);

  /* Set expectations for chain 2 */
  expect_digitalWrite(handle2.pinLatch, HIGH);
  expect_shiftInOneChip(&handle2, expected_buffer2[0]);
  expect_digitalWrite(handle2.pinLatch, LOW);

  /* Test read from chain 1 */
  shreg_read(&handle1, read_buffer);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    expected_buffer1, read_buffer, handle1.numChips,
    "Incorrect data read from the chain 1");

  /* Test read from chain 2 */
  shreg_read(&handle2, read_buffer);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    expected_buffer2, read_buffer, handle2.numChips,
    "Incorrect data read from the chain 2");
}

