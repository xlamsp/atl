#include "mocks.h"
#include "unity_fixture.h"

static mocks_return_code verify_assert_value;

TEST_GROUP(EmptyContext);

TEST_SETUP(EmptyContext)
{
  mocks_init();
}

TEST_TEAR_DOWN(EmptyContext)
{
  TEST_ASSERT_EQUAL(verify_assert_value, mocks_verify());
}

/*
 * "expect" called once should succeed
 * "verify" after "expect" without "invoke" should fail
 */
TEST(EmptyContext, ExpectCalledOnceSucceeds)
{
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, NULL, 0));
  verify_assert_value = mocks_not_all_expectations_used;
}

/*
 * "invoke" called once prior to "expect" should fail
 */
TEST(EmptyContext, InvokeCalledBeforeExpectFails)
{
  TEST_ASSERT_EQUAL(mocks_no_more_expectations, mocks_invoke(0, NULL, 0));
  verify_assert_value = mocks_no_more_expectations;
}

/*
 * "verify" called alone should succeed
 */
TEST(EmptyContext, VerifyCalledAloneSucceeds)
{
  verify_assert_value = mocks_success;
}

/*
 * "invoke" after "expect" with the same ID should succeed
 * "verify" after successful "expect" and "invoke" should succeed
 */
TEST(EmptyContext, InvokeMatchingExpectSucceeds)
{
  mocks_expect(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, NULL, 0));
  verify_assert_value = mocks_success;
}

/*
 * "invoke" after "expect" with a different ID should fail
 */
TEST(EmptyContext, InvokeNotMatchingExpectFails)
{
  mocks_expect(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_not_matching_id, mocks_invoke(1, NULL, 0));
  verify_assert_value = mocks_not_matching_id;
}

/*
 * "expect" after previous failure should fail
 */
TEST(EmptyContext,ExpectAfterPreviousFailFails)
{
  /*
   * call "invoke" before "expect" to set mocks in a error state
   */
  mocks_invoke(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_no_more_expectations, mocks_expect(0, NULL, 0));
  verify_assert_value = mocks_no_more_expectations;
}

/*
 * "expect" called twice should succeed
 */
TEST(EmptyContext, ExpectCalledTwiceSucceeds)
{
  mocks_expect(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, NULL, 0));
  verify_assert_value = mocks_not_all_expectations_used;
}

/*
 * "invoke" called once after "expect" twice should succeed, "verify" fail
 */
TEST(EmptyContext, InvokeOnceAfterExpectTwiceSucceeds)
{
  mocks_expect(0, NULL, 0);
  mocks_expect(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, NULL, 0));
  verify_assert_value = mocks_not_all_expectations_used;
}

/*
 * "invoke" called twice after "expect" twice should succeed, "verify" succeed
 */
TEST(EmptyContext, InvokeTwiceAfterExpectTwiceSucceeds)
{
  mocks_expect(0, NULL, 0);
  mocks_expect(0, NULL, 0);
  mocks_invoke(0, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, NULL, 0));
  verify_assert_value = mocks_success;
}

/*
 * "expect" called twice with different IDs following "invoke" twice with
 * matching IDs should succeed
 */
TEST(EmptyContext, InvokeTwiceAfterExpectTwiceDifferentMatchingIDsSucceeds)
{
  mocks_expect(0, NULL, 0);
  mocks_expect(1, NULL, 0);
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, NULL, 0));
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(1, NULL, 0));
  verify_assert_value = mocks_success;
}

