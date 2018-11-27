#include "mocks.h"

mocks_return_code
mocks_expect(int id, void *ctx, int size)
{
  return mocks_not_initialized;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  return mocks_not_initialized;
}

