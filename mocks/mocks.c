#include <stdint.h>
#include <string.h>
#include "mocks.h"


static int expect_count;
static int invoke_count;
static int expected_id[MOCKS_MAX_EXPECTATIONS_NUMBER];
static uint8_t expected_ctx[MOCKS_MAX_CONTEXT_DATA_SIZE];
static int expected_size[MOCKS_MAX_EXPECTATIONS_NUMBER];
static void *expected_ctx_ptr[MOCKS_MAX_EXPECTATIONS_NUMBER];
static int expected_ctx_used;
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
  expected_ctx_used = 0;
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

  if (size > MOCKS_MAX_CONTEXT_DATA_SIZE) {
    last_error = mocks_no_room_for_ctx_data;
    return last_error;
  }

  expected_id[expect_count] = id;
  expected_ctx_ptr[expect_count] = &expected_ctx[expected_ctx_used];
  expected_size[expect_count] = size;
  memcpy(expected_ctx_ptr[expect_count], ctx, size);
  expected_ctx_used += size;
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

  if (size != expected_size[invoke_count]) {
    last_error = mocks_ctx_size_mismatch;
    return last_error;
  }

  memcpy(ctx, expected_ctx_ptr[invoke_count], size);

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

