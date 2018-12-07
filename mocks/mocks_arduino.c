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

void
pinMode(uint8_t pin, uint8_t mode)
{
  ctx_pinMode ctx;

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_pinMode, &ctx, sizeof(ctx)),
    "pinMode: mocks_invoke failed");

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

void
digitalWrite(uint8_t pin, uint8_t val)
{
  ctx_digitalWrite ctx;

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_digitalWrite, &ctx, sizeof(ctx)),
    "digitalWrite: mocks_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pin, pin,
    "digitalWrite: pin not match");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.val, val,
    "digitalWrite: val not match");
}


typedef struct {
  int16_t ret;
  uint8_t pin;
} ctx_digitalRead;

void
expect_digitalRead(int16_t ret, uint8_t pin)
{
  ctx_digitalRead ctx;

  ctx.ret = ret;
  ctx.pin = pin;
  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_expect(mock_id_digitalRead, &ctx, sizeof(ctx)),
    "expect_digitalRead: mocks_expect failed");
}

int16_t
digitalRead(uint8_t pin)
{
  ctx_digitalRead ctx;

  TEST_ASSERT_EQUAL_MESSAGE(mocks_success,
    mocks_invoke(mock_id_digitalRead, &ctx, sizeof(ctx)),
    "digitalRead: mocks_invoke failed");

  TEST_ASSERT_EQUAL_UINT8_MESSAGE(ctx.pin, pin,
    "digitalRead: pin not match");

  return ctx.ret;
}

