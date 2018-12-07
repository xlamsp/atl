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

