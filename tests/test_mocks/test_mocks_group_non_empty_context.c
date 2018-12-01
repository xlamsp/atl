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

/*
 * "invoke" with non-null ctx and zero size should fail
 */
TEST(NonEmptyContext, InvokeNonNullCtxZeroSizeFails)
{
  int ctx;

  mocks_expect(0, &ctx, sizeof(ctx));
  TEST_ASSERT_EQUAL(mocks_invalid_ctx_size, mocks_invoke(0, &ctx, 0));
  verify_assert_value = mocks_invalid_ctx_size;
}

/*
 * "invoke" with null ctx and non-zero size should fail
 */
TEST(NonEmptyContext, InvokeNullCtxNonZeroSizeFails)
{
  int ctx;

  mocks_expect(0, &ctx, sizeof(ctx));
  TEST_ASSERT_EQUAL(mocks_invalid_ctx, mocks_invoke(0, NULL, sizeof(ctx)));
  verify_assert_value = mocks_invalid_ctx;
}

/*
 * "invoke" with not matching size should fail
 */
TEST(NonEmptyContext, InvokeCtxSizeNotMatchFails)
{
  int ctx;

  mocks_expect(0, &ctx, sizeof(ctx));
  TEST_ASSERT_EQUAL(mocks_ctx_size_mismatch,
                    mocks_invoke(0, &ctx, sizeof(ctx) + 1));
  verify_assert_value = mocks_ctx_size_mismatch;
}

/*
 * "invoke" with non-null ctx and matching non-zero size should succeed
 */
TEST(NonEmptyContext, InvokeCtxSizeMatchSucceeds)
{
  int ctx;

  mocks_expect(0, &ctx, sizeof(ctx));
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, &ctx, sizeof(ctx)));
  verify_assert_value = mocks_success;
}

/*
 * "invoke" should return ctx data provided by "expect"
 */
TEST(NonEmptyContext, InvokeReturnsCtxProvidedByExpect)
{
  int ctx_expect = 1234;
  int ctx_invoke = 5678;

  mocks_expect(0, &ctx_expect, sizeof(ctx_expect));
  mocks_invoke(0, &ctx_invoke, sizeof(ctx_invoke));
  TEST_ASSERT_EQUAL(1234, ctx_invoke);
  verify_assert_value = mocks_success;
}

/*
 * "expect" should make copy of ctx data to protect it from corruption
 */
TEST(NonEmptyContext, ExpectShouldMakeCopyOfCtxData)
{
  int ctx_expect = 1234;
  int ctx_invoke = 5678;

  mocks_expect(0, &ctx_expect, sizeof(ctx_expect));
  ctx_expect = 9876; /* corrupt original ctx data */
  mocks_invoke(0, &ctx_invoke, sizeof(ctx_invoke));
  TEST_ASSERT_EQUAL(1234, ctx_invoke);
  verify_assert_value = mocks_success;
}

