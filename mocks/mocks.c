#include <stdint.h>
#include <string.h>
#include "mocks.h"


static int expect_count;
static int invoke_count;
static int expected_id[MOCKS_MAX_EXPECTATIONS_NUMBER];
static uint8_t expected_ctx[256];
static int expected_size;
static mocks_return_code last_error = mocks_not_initialized;


#define exit_if_error(error) {              \
  mocks_return_code error_value = (error);  \
  if (error_value != mocks_success) {       \
    return error_value;                     \
  }                                         \
}


/*******************************************************************************
 * Local functions
 ******************************************************************************/

static inline mocks_return_code
check_context_ctx(void *ctx, int size)
{
  if (ctx == NULL && size != 0) {
    last_error = mocks_invalid_ctx;
  }
  return last_error;
}

static inline mocks_return_code
check_context_ctx_size(void *ctx, int size)
{
  if (ctx != NULL && size == 0) {
    last_error = mocks_invalid_ctx_size;
  }
  return last_error;
}

static mocks_return_code
check_context(void *ctx, int size)
{
  exit_if_error(last_error);
  exit_if_error(check_context_ctx(ctx, size));
  return check_context_ctx_size(ctx, size);
}


/*******************************************************************************
 * Public functions
 ******************************************************************************/

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
  exit_if_error(check_context(ctx, size));

  if (expect_count >= MOCKS_MAX_EXPECTATIONS_NUMBER) {
    last_error = mocks_no_room_for_expectation;
    return last_error;
  }

  expected_id[expect_count] = id;
  memcpy(expected_ctx, ctx, size);
  expected_size = size;
  expect_count++;

  return mocks_success;
}

mocks_return_code
mocks_invoke(int id, void *ctx, int size)
{
  exit_if_error(check_context(ctx, size));

  if (invoke_count >= expect_count) {
    last_error = mocks_no_more_expectations;
    return last_error;
  }

  if (id != expected_id[invoke_count]) {
    last_error = mocks_not_matching_id;
    return last_error;
  }

  if (size != expected_size) {
    last_error = mocks_ctx_size_mismatch;
    return last_error;
  }

  memcpy(ctx, expected_ctx, size);

  invoke_count++;

  return mocks_success;
}

mocks_return_code
mocks_verify(void)
{
  exit_if_error(last_error);

  if (invoke_count < expect_count) {
    return mocks_not_all_expectations_used;
  }

  return mocks_success;
}

