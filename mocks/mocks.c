#include "mocks.h"

static int expect_count;
static int expected_id;
static mocks_return_code last_error = mocks_not_initialized;

void
mocks_init(void)
{
  expect_count = 0;
  last_error = mocks_success;
}

mocks_return_code
mocks_expect(int id, void *ctx, int size)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  expect_count++;
  expected_id = id;
  return last_error;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (!expect_count) {
    last_error = mocks_no_more_expectations;
    return mocks_no_more_expectations;
  }

  if (id != expected_id) {
    last_error = mocks_not_matching_id;
    return last_error;
  }

  expect_count--;

  return mocks_success;
}

mocks_return_code
mocks_verify(void)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (expect_count) {
    return mocks_not_all_expectations_used;
  }

  return last_error;
}

