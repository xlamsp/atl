#include <stdint.h>
#include <string.h>
#include "mocks.h"


static int expect_count;
static int invoke_count;
static struct {
  int id;
  void *ctx;
  unsigned int size;
} expected[MOCKS_MAX_EXPECTATIONS_NUMBER];
static uint8_t expected_ctx[MOCKS_MAX_CONTEXT_DATA_SIZE];
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
check_context_ctx(void *ctx, unsigned int size)
{
  if (ctx == NULL && size != 0) {
    last_error = mocks_invalid_ctx;
  }
  return last_error;
}

static inline mocks_return_code
check_context_ctx_size(void *ctx, unsigned int size)
{
  if (ctx != NULL && size == 0) {
    last_error = mocks_invalid_ctx_size;
  }
  return last_error;
}

static mocks_return_code
check_context(void *ctx, unsigned int size)
{
  exit_if_error(last_error);
  exit_if_error(check_context_ctx(ctx, size));
  return check_context_ctx_size(ctx, size);
}

static inline mocks_return_code
check_room_for_expectation(void)
{
  if (expect_count >= MOCKS_MAX_EXPECTATIONS_NUMBER) {
    last_error = mocks_no_room_for_expectation;
  }
  return last_error;
}

static inline mocks_return_code
check_room_for_ctx_data(unsigned int size)
{
  if (size > MOCKS_MAX_CONTEXT_DATA_SIZE - expected_ctx_used) {
    last_error = mocks_no_room_for_ctx_data;
  }
  return last_error;
}

static inline mocks_return_code
check_for_more_expectations(void)
{
  if (invoke_count >= expect_count) {
    last_error = mocks_no_more_expectations;
  }
  return last_error;
}

static inline mocks_return_code
check_for_not_matching_id(int id)
{
  if (id != expected[invoke_count].id) {
    last_error = mocks_not_matching_id;
  }
  return last_error;
}

static inline mocks_return_code
check_for_ctx_size_mismatch(unsigned int size)
{
  if (size != expected[invoke_count].size) {
    last_error = mocks_ctx_size_mismatch;
  }
  return last_error;
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
mocks_expect(int id, void *ctx, unsigned int size)
{
  exit_if_error(check_context(ctx, size));
  exit_if_error(check_room_for_expectation());
  exit_if_error(check_room_for_ctx_data(size));

  expected[expect_count].id = id;
  expected[expect_count].ctx = &expected_ctx[expected_ctx_used];
  expected[expect_count].size = size;
  memcpy(expected[expect_count].ctx, ctx, size);
  expected_ctx_used += size;
  expect_count++;

  return mocks_success;
}

mocks_return_code
mocks_invoke(int id, void *ctx, unsigned int size)
{
  exit_if_error(check_context(ctx, size));
  exit_if_error(check_for_more_expectations());
  exit_if_error(check_for_not_matching_id(id));
  exit_if_error(check_for_ctx_size_mismatch(size));

  memcpy(ctx, expected[invoke_count].ctx, size);
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

char *
mocks_errstr(mocks_return_code err)
{
  switch (err) {
  case mocks_success:
    return "success";
  case mocks_not_initialized:
    return "not initialized";
  case mocks_no_more_expectations:
    return "no more expectations";
  case mocks_not_all_expectations_used:
    return "not all expectations used";
  case mocks_not_matching_id:
    return "not matching id";
  case mocks_no_room_for_expectation:
    return "no room for expectation";
  case mocks_invalid_ctx_size:
    return "invalid ctx size";
  case mocks_invalid_ctx:
    return "invalid ctx";
  case mocks_ctx_size_mismatch:
    return "ctx size mismatch";
  case mocks_no_room_for_ctx_data:
    return "no room for ctx data";
  default:
    return "unknown error";
  }
}

