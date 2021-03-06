#include "mocks.h"
#include "unity_fixture.h"

static mocks_return_code verify_assert_value;
static uint8_t expect_ctx[MOCKS_MAX_CONTEXT_DATA_SIZE];
static uint8_t invoke_ctx[MOCKS_MAX_CONTEXT_DATA_SIZE];

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

/*
 * "expect" with ctx data size up to the maximum context buffer should succeed
 */
TEST(NonEmptyContext, ExpectWithCtxDataUpToMaxBufferSizeSucceeds)
{
  int i;

  /* init expected and invoked context data */
  for (i = 0; i < MOCKS_MAX_CONTEXT_DATA_SIZE; i++) {
    expect_ctx[i] = (uint8_t)i;
    invoke_ctx[i] = (uint8_t)(i + 10);
  }

  TEST_ASSERT_EQUAL(mocks_success,
                    mocks_expect(0, &expect_ctx, MOCKS_MAX_CONTEXT_DATA_SIZE));

  /* corrupt expected context data */
  for (i = 0; i < MOCKS_MAX_CONTEXT_DATA_SIZE; i++) {
    expect_ctx[i] = (uint8_t)(i + 20);
  }

  TEST_ASSERT_EQUAL(mocks_success,
                    mocks_invoke(0, &invoke_ctx, MOCKS_MAX_CONTEXT_DATA_SIZE));

  /* verify that invoked context data matches expected context data */
  for (i = 0; i < MOCKS_MAX_CONTEXT_DATA_SIZE; i++) {
    TEST_ASSERT_EQUAL_UINT8(i, invoke_ctx[i]);
  }

  verify_assert_value = mocks_success;
}

/*
 * "expect" with ctx data size over the maximum context buffer should fail
 */
TEST(NonEmptyContext, ExpectCtxDataOverMaxBufferSizeFails)
{
  TEST_ASSERT_EQUAL(mocks_no_room_for_ctx_data,
                mocks_expect(0, &expect_ctx, MOCKS_MAX_CONTEXT_DATA_SIZE + 1));
  verify_assert_value = mocks_no_room_for_ctx_data;
}

/*
 * "invoke" called twice after "expect" twice should succeed, ctx data should
 *  match
 */
TEST(NonEmptyContext, ExpectTwiceInvokeTwiceMatchingNonEmptyCtxSucceeds)
{
  int ctx_expect;
  int ctx_invoke;

  ctx_expect = 1234;
  mocks_expect(0, &ctx_expect, sizeof(ctx_expect));

  ctx_expect = 5678;
  TEST_ASSERT_EQUAL(mocks_success,
                    mocks_expect(0, &ctx_expect, sizeof(ctx_expect)));

  TEST_ASSERT_EQUAL(mocks_success,
                    mocks_invoke(0, &ctx_invoke, sizeof(ctx_invoke)));
  TEST_ASSERT_EQUAL(1234, ctx_invoke);

  TEST_ASSERT_EQUAL(mocks_success,
                    mocks_invoke(0, &ctx_invoke, sizeof(ctx_invoke)));
  TEST_ASSERT_EQUAL(5678, ctx_invoke);

  verify_assert_value = mocks_success;
}

/*
 * "expect" and "invoke" called multiple times with total ctx sizes up to max
 *  contex buffer should succeed
 */
TEST(NonEmptyContext, MultipleExpectWithCtxDataUpToMaxBufferSizeSucceeds)
{
  int i;
  unsigned int size;

  size = MOCKS_MAX_CONTEXT_DATA_SIZE / 3;
  for (i = 0; i < size; i++) {
    expect_ctx[i] = (uint8_t)i;
  }
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, &expect_ctx, size));

  size = MOCKS_MAX_CONTEXT_DATA_SIZE - size;
  for (i = 0; i < size; i++) {
    expect_ctx[i] = (uint8_t)(i * 2);
  }
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, &expect_ctx, size));

  size = MOCKS_MAX_CONTEXT_DATA_SIZE / 3;
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, &invoke_ctx, size));
  for (i = 0; i < size; i++) {
    TEST_ASSERT_EQUAL_UINT8(i, invoke_ctx[i]);
  }

  size = MOCKS_MAX_CONTEXT_DATA_SIZE - size;
  TEST_ASSERT_EQUAL(mocks_success, mocks_invoke(0, &invoke_ctx, size));
  for (i = 0; i < size; i++) {
    TEST_ASSERT_EQUAL_UINT8((i * 2), invoke_ctx[i]);
  }

  verify_assert_value = mocks_success;
}

/*
 * "expect" called multiple times with total ctx sizes over max contex buffer
 * should fail
 */
TEST(NonEmptyContext, MultipleExpectWithCtxDataOverMaxBufferFails)
{
  unsigned int size;

  size = MOCKS_MAX_CONTEXT_DATA_SIZE / 3;
  TEST_ASSERT_EQUAL(mocks_success, mocks_expect(0, &expect_ctx, size));

  size = MOCKS_MAX_CONTEXT_DATA_SIZE - size + 1;
  TEST_ASSERT_EQUAL(mocks_no_room_for_ctx_data,
                    mocks_expect(0, &expect_ctx, size));

  verify_assert_value = mocks_no_room_for_ctx_data;
}

