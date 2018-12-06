#include "mocks.h"
#include "unity_fixture.h"

TEST_GROUP(Misc);

TEST_SETUP(Misc)
{
}

TEST_TEAR_DOWN(Misc)
{
}

/*
 * convert mocks error codes to the corresponding text strings
 */
TEST(Misc, ConvertMocksErrorsToTheStrings)
{
  TEST_ASSERT_EQUAL_STRING("success",
                           mocks_errstr(mocks_success));
  TEST_ASSERT_EQUAL_STRING("not initialized",
                           mocks_errstr(mocks_not_initialized));
  TEST_ASSERT_EQUAL_STRING("no more expectations",
                           mocks_errstr(mocks_no_more_expectations));
  TEST_ASSERT_EQUAL_STRING("not all expectations used",
                           mocks_errstr(mocks_not_all_expectations_used));
  TEST_ASSERT_EQUAL_STRING("not matching id",
                           mocks_errstr(mocks_not_matching_id));
  TEST_ASSERT_EQUAL_STRING("no room for expectation",
                           mocks_errstr(mocks_no_room_for_expectation));
  TEST_ASSERT_EQUAL_STRING("invalid ctx size",
                           mocks_errstr(mocks_invalid_ctx_size));
  TEST_ASSERT_EQUAL_STRING("invalid ctx",
                           mocks_errstr(mocks_invalid_ctx));
  TEST_ASSERT_EQUAL_STRING("ctx size mismatch",
                           mocks_errstr(mocks_ctx_size_mismatch));
  TEST_ASSERT_EQUAL_STRING("no room for ctx data",
                           mocks_errstr(mocks_no_room_for_ctx_data));
  TEST_ASSERT_EQUAL_STRING("unknown error",
                           mocks_errstr(-1));
}

