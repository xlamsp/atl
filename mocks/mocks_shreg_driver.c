#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

/*
 * mock shreg_driver shreg_init_input()
 */
typedef shreg_driver_t ctx_shreg_init_input;

void
expect_shreg_init_input(shreg_driver_t *handle)
{
  ctx_shreg_init_input ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "expect_shreg_init_input: handle must not be NULL");

  memcpy(&ctx, handle, sizeof(ctx));
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_shreg_init_input, &ctx, sizeof(ctx)),
    "expect_shreg_init_input: mocks_expect failed");
}

void
shreg_init_input(shreg_driver_t *handle)
{
  ctx_shreg_init_input ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "shreg_init_input: handle must not be NULL");

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_shreg_init_input, &ctx, sizeof(ctx)),
    "shreg_init_input: mocks_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinLatch, handle->pinLatch,
    "shreg_init_input: pinLatch not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinClock, handle->pinClock,
    "shreg_init_input: pinClock not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinData, handle->pinData,
    "shreg_init_input: pinData not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.numChips, handle->numChips,
    "shreg_init_input: numChips not match");
}


/*
 * mock shreg_driver shreg_init_output()
 */
typedef shreg_driver_t ctx_shreg_init_output;

void
expect_shreg_init_output(shreg_driver_t *handle)
{
  ctx_shreg_init_output ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "expect_shreg_init_output: handle must not be NULL");

  memcpy(&ctx, handle, sizeof(ctx));
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_shreg_init_output, &ctx, sizeof(ctx)),
    "expect_shreg_init_output: mocks_expect failed");
}

void
shreg_init_output(shreg_driver_t *handle)
{
  ctx_shreg_init_output ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "shreg_init_output: handle must not be NULL");

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_shreg_init_output, &ctx, sizeof(ctx)),
    "shreg_init_output: mocks_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinLatch, handle->pinLatch,
    "shreg_init_output: pinLatch not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinClock, handle->pinClock,
    "shreg_init_output: pinClock not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pinData, handle->pinData,
    "shreg_init_output: pinData not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.numChips, handle->numChips,
    "shreg_init_output: numChips not match");
}


/*
 * mock shreg_driver shreg_read()
 */
typedef struct {
  shreg_driver_t handle;
  uint8_t buffer[MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE];
} ctx_shreg_read;

void
expect_shreg_read(shreg_driver_t *handle, uint8_t *buffer)
{
  ctx_shreg_read ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "expect_shreg_read: handle must not be NULL");

  TEST_ASSERT_NOT_NULL_MESSAGE(buffer,
    "expect_shreg_read: buffer must not be NULL");

  TEST_ASSERT_LESS_OR_EQUAL_UINT8_MESSAGE(
    MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE, handle->numChips,
    "expect_shreg_read: handle->numChips "
    "must not exceed MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE");

  memcpy(&(ctx.handle), handle, sizeof(ctx.handle));
  memcpy(ctx.buffer, buffer, handle->numChips);
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_shreg_read, &ctx, sizeof(ctx)),
    "expect_shreg_read: mocks_expect failed");
}

void
shreg_read(shreg_driver_t *handle, uint8_t *buffer)
{
  ctx_shreg_read ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "shreg_read: handle must not be NULL");

  TEST_ASSERT_NOT_NULL_MESSAGE(buffer,
    "shreg_read: buffer must not be NULL");

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_shreg_read, &ctx, sizeof(ctx)),
    "shreg_read: mocks_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.handle.pinLatch, handle->pinLatch,
    "shreg_read: pinLatch not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.handle.pinClock, handle->pinClock,
    "shreg_read: pinClock not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.handle.pinData, handle->pinData,
    "shreg_read: pinData not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.handle.numChips, handle->numChips,
    "shreg_read: numChips not match");

  memcpy(buffer, ctx.buffer, ctx.handle.numChips);
}

