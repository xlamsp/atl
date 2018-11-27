#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(Init);

TEST_SETUP(Init)
{
}

TEST_TEAR_DOWN(Init)
{
}

/*
 * "expect" called prior to "init" should fail
 */
TEST(Init, ExpectPriorToInitFails)
{
  TEST_ASSERT_EQUAL(mocks_not_initialized, mocks_expect(0, NULL, 0));
}

/*
 * "invoke" called prior to "init" should fail
 */
TEST(Init, InvokePriorToInitFails)
{
  TEST_ASSERT_EQUAL(mocks_not_initialized, mocks_invoke(0, NULL, 0));
}

/*
 * "verify" called prior to "init" should fail
 */
TEST(Init, VerifyPriorToInitFails)
{
  TEST_ASSERT_EQUAL(mocks_not_initialized, mocks_verify());
}

