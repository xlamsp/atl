#include "mocks.h"

static mocks_return_code last_error = mocks_not_initialized;

void
mocks_init(void)
{
  last_error = mocks_success;
}

mocks_return_code
mocks_expect(int id, void *ctx, int size)
{
  return last_error;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  return last_error;
}

mocks_return_code
mocks_verify(void)
{
  return last_error;
}

