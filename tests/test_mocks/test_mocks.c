#include "unity_fixture.h"

TEST_GROUP_RUNNER(Init)
{
  RUN_TEST_CASE(Init, ExpectPriorToInitFails);
  RUN_TEST_CASE(Init, InvokePriorToInitFails);
  RUN_TEST_CASE(Init, VerifyPriorToInitFails);
}

TEST_GROUP_RUNNER(EmptyContext)
{
  RUN_TEST_CASE(EmptyContext, ExpectCalledOnceSucceeds);
  RUN_TEST_CASE(EmptyContext, InvokeCalledBeforeExpectFails);
  RUN_TEST_CASE(EmptyContext, VerifyCalledAloneSucceeds);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Init);
  RUN_TEST_GROUP(EmptyContext);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}
