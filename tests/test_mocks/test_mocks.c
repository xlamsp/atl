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
  RUN_TEST_CASE(EmptyContext, InvokeMatchingExpectSucceeds);
  RUN_TEST_CASE(EmptyContext, InvokeNotMatchingExpectFails);
  RUN_TEST_CASE(EmptyContext, ExpectAfterPreviousFailFails);
  RUN_TEST_CASE(EmptyContext, ExpectCalledTwiceSucceeds);
  RUN_TEST_CASE(EmptyContext, InvokeOnceAfterExpectTwiceSucceeds);
  RUN_TEST_CASE(EmptyContext, InvokeTwiceAfterExpectTwiceSucceeds);
  RUN_TEST_CASE(EmptyContext,
    InvokeTwiceAfterExpectTwiceDifferentMatchingIDsSucceeds);
  RUN_TEST_CASE(EmptyContext, InvokeAfterExpectTwiceNotMatchingIdFails);
  RUN_TEST_CASE(EmptyContext, ExpectAndInvokeUpToMaxNumberSucceeds);
  RUN_TEST_CASE(EmptyContext, ExpectOverMaxNumberFails);
}

TEST_GROUP_RUNNER(NonEmptyContext)
{
  RUN_TEST_CASE(NonEmptyContext, ExpectNonNullCtxZeroSizeFails);
  RUN_TEST_CASE(NonEmptyContext, ExpectNullCtxNonZeroSizeFails);
  RUN_TEST_CASE(NonEmptyContext, ExpectNonNullCtxNonZeroSizeSucceeds);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Init);
  RUN_TEST_GROUP(EmptyContext);
  RUN_TEST_GROUP(NonEmptyContext);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}
