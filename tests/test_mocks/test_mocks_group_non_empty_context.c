#include "mocks.h"
#include "unity_fixture.h"

static mocks_return_code verify_assert_value;

TEST_GROUP(NonEmptyContext);

TEST_SETUP(NonEmptyContext)
{
  mocks_init();
}

TEST_TEAR_DOWN(NonEmptyContext)
{
  TEST_ASSERT_EQUAL(verify_assert_value, mocks_verify());
}

/*
 * "expect" with non-null ctx and zero size should fail
 */
TEST(NonEmptyContext, ExpectNonNullCtxZeroSizeFails)
{
  int ctx;

  TEST_ASSERT_EQUAL(mocks_invalid_ctx_size, mocks_expect(0, &ctx, 0));
  verify_assert_value = mocks_invalid_ctx_size;
}

/*
 * "expect" with null ctx and non-zero size should fail
 */
TEST(NonEmptyContext, ExpectNullCtxNonZeroSizeFails)
{
  TEST_ASSERT_EQUAL(mocks_invalid_ctx, mocks_expect(0, NULL, 1));
  verify_assert_value = mocks_invalid_ctx;
}

/*
 * "expect" with non-null ctx and small non-zero size should succeed
 */
TEST(NonEmptyContext, ExpectNonNullCtxNonZeroSizeSucceeds)
{
  int ctx;

  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, &ctx, sizeof(ctx)));
  verify_assert_value = mocks_not_all_expectations_used;
}

