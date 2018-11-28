#include "mocks.h"

static int expect_count;
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
  expect_count = 1;
  return last_error;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  if (last_error != mocks_success) {
    return last_error;
  }

  if (expect_count) {
    return mocks_success;
  }

  return mocks_no_more_expectations;
}

mocks_return_code
mocks_verify(void)
{
  return last_error;
}

