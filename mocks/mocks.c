#include "mocks.h"

static int expect_count;
static int invoke_count;
static int expected_id[MOCKS_MAX_EXPECTATIONS_NUMBER];
static mocks_return_code last_error = mocks_not_initialized;

void
mocks_init(void)
{
  expect_count = 0;
  invoke_count = 0;
  last_error = mocks_success;
}

mocks_return_code
mocks_expect(int id, void *ctx, int size)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (expect_count >= MOCKS_MAX_EXPECTATIONS_NUMBER) {
    last_error = mocks_no_room_for_expectation;
    return last_error;
  }

  expected_id[expect_count] = id;
  expect_count++;

  return mocks_success;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (invoke_count >= expect_count) {
    last_error = mocks_no_more_expectations;
    return last_error;
  }

  if (id != expected_id[invoke_count]) {
    last_error = mocks_not_matching_id;
    return last_error;
  }

  invoke_count++;

  return mocks_success;
}

mocks_return_code
mocks_verify(void)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (invoke_count < expect_count) {
    return mocks_not_all_expectations_used;
  }

  return mocks_success;
}

