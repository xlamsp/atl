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

