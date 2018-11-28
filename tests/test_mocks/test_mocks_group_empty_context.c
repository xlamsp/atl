#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(EmptyContext);

TEST_SETUP(EmptyContext)
{
  mocks_init();
}

TEST_TEAR_DOWN(EmptyContext)
{
}

/*
 * "expect" called once should succeed
 */
TEST(EmptyContext, ExpectCalledOnceSucceeds)
{
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, NULL, 0));
}

/*
 * "invoke" called once prior to "expect" should fail
 */
TEST(EmptyContext, InvokeCalledBeforeExpectFails)
{
  TEST_ASSERT_EQUAL(mocks_no_more_expectations, mocks_invoke(0, NULL, 0));
}

