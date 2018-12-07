#include "mocks_arduino.h"
#include "unity_fixture.h"

typedef struct {
  uint8_t pin;
  uint8_t mode;
} ctx_pinMode;

void
expect_pinMode(uint8_t pin, uint8_t mode)
{
  ctx_pinMode ctx;

  ctx.pin = pin;
  ctx.mode = mode;
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_pinMode, &ctx, sizeof(ctx)),
    "expect_pinMode: mocks_expect failed");
}

void pinMode(uint8_t pin, uint8_t mode)
{
  ctx_pinMode ctx;

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_pinMode, &ctx, sizeof(ctx)),
    "pinMode: mock_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pin, pin,
    "pinMode: pin not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.mode, mode,
    "pinMode: mode not match");
}


typedef struct {
  uint8_t pin;
  uint8_t val;
} ctx_digitalWrite;

void
expect_digitalWrite(uint8_t pin, uint8_t val)
{
  ctx_digitalWrite ctx;

  ctx.pin = pin;
  ctx.val = val;
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_digitalWrite, &ctx, sizeof(ctx)),
    "expect_digitalWrite: mocks_expect failed");
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  ctx_digitalWrite ctx;

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_digitalWrite, &ctx, sizeof(ctx)),
    "digitalWrite: mock_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pin, pin,
    "digitalWrite: pin not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.val, val,
    "digitalWrite: val not match");
}

