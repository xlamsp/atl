#include "mocks_arduino.h"
#include "unity_fixture.h"

TEST_GROUP(Arduino);

TEST_SETUP(Arduino)
{
  mocks_init();
}

TEST_TEAR_DOWN(Arduino)
{
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success, mocks_verify(),
    "TEST_TEAR_DOWN: mocks_verify failed");
}

/*
 * mock arduino pinMode()
 */
TEST(Arduino, pinMode)
{
  expect_pinMode(10, OUTPUT);
  pinMode(10, OUTPUT);
}

/*
 * mock arduino digitalWrite()
 */
TEST(Arduino, digitalWrite)
{
  expect_digitalWrite(10, HIGH);
  digitalWrite(10, HIGH);
}

/*
 * mock arduino digitalRead()
 */
TEST(Arduino, digitalRead)
{
  expect_digitalRead(HIGH, 10);
  TEST_ASSERT_EQUAL_INT16_MESSAGE(HIGH, digitalRead(10),
    "return value not match");
}

/*
 * mock arduino millis()
 */
TEST(Arduino, millis)
{
  expect_millis(0x87654321);
  TEST_ASSERT_EQUAL_UINT32_MESSAGE(0x87654321, millis(),
    "return value not match");
}

