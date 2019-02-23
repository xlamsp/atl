#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>


/*
 * mock shreg_driver service functions
 */
static void
mocks_shreg_verify_handle(shreg_driver_t *expected, shreg_driver_t *actual)
{
  TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected->pinLatch, actual->pinLatch,
    "pinLatch not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected->pinClock, actual->pinClock,
    "pinClock not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected->pinData, actual->pinData,
    "pinData not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected->numChips, actual->numChips,
    "numChips not match");
}


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

  mocks_shreg_verify_handle(&ctx, handle);
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

  mocks_shreg_verify_handle(&ctx, handle);
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

  mocks_shreg_verify_handle(&(ctx.handle), handle);

  memcpy(buffer, ctx.buffer, ctx.handle.numChips);
}


/*
 * mock shreg_driver shreg_write()
 */
typedef struct {
  shreg_driver_t handle;
  uint8_t buffer[MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE];
} ctx_shreg_write;

void
expect_shreg_write(shreg_driver_t *handle, uint8_t *buffer)
{
  ctx_shreg_write ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "expect_shreg_write: handle must not be NULL");

  TEST_ASSERT_NOT_NULL_MESSAGE(buffer,
    "expect_shreg_write: buffer must not be NULL");

  TEST_ASSERT_LESS_OR_EQUAL_UINT8_MESSAGE(
    MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE, handle->numChips,
    "expect_shreg_write: handle->numChips "
    "must not exceed MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE");

  memcpy(&(ctx.handle), handle, sizeof(ctx.handle));
  memcpy(ctx.buffer, buffer, handle->numChips);
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_shreg_write, &ctx, sizeof(ctx)),
    "expect_shreg_write: mocks_expect failed");
}

void
shreg_write(shreg_driver_t *handle, uint8_t *buffer)
{
  ctx_shreg_write ctx;

  TEST_ASSERT_NOT_NULL_MESSAGE(handle,
    "shreg_write: handle must not be NULL");

  TEST_ASSERT_NOT_NULL_MESSAGE(buffer,
    "shreg_write: buffer must not be NULL");

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_shreg_write, &ctx, sizeof(ctx)),
    "shreg_write: mocks_invoke failed");

  mocks_shreg_verify_handle(&(ctx.handle), handle);

  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(
    ctx.buffer, buffer, handle->numChips,
    "shreg_write: incorrect data written to the chain");
}

