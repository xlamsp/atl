#include "mocks_shreg_driver.h"
#include "unity_fixture.h"
#include <string.h>

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

