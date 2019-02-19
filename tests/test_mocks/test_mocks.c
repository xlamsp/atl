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
  RUN_TEST_CASE(NonEmptyContext, InvokeNonNullCtxZeroSizeFails);
  RUN_TEST_CASE(NonEmptyContext, InvokeNullCtxNonZeroSizeFails);
  RUN_TEST_CASE(NonEmptyContext, InvokeCtxSizeNotMatchFails);
  RUN_TEST_CASE(NonEmptyContext, InvokeCtxSizeMatchSucceeds);
  RUN_TEST_CASE(NonEmptyContext, InvokeReturnsCtxProvidedByExpect);
  RUN_TEST_CASE(NonEmptyContext, ExpectShouldMakeCopyOfCtxData);
  RUN_TEST_CASE(NonEmptyContext, ExpectWithCtxDataUpToMaxBufferSizeSucceeds);
  RUN_TEST_CASE(NonEmptyContext, ExpectCtxDataOverMaxBufferSizeFails);
  RUN_TEST_CASE(NonEmptyContext,
    ExpectTwiceInvokeTwiceMatchingNonEmptyCtxSucceeds);
  RUN_TEST_CASE(NonEmptyContext,
    MultipleExpectWithCtxDataUpToMaxBufferSizeSucceeds);
  RUN_TEST_CASE(NonEmptyContext, MultipleExpectWithCtxDataOverMaxBufferFails);
}

TEST_GROUP_RUNNER(Misc)
{
  RUN_TEST_CASE(Misc, ConvertMocksErrorsToTheStrings);
}

TEST_GROUP_RUNNER(Arduino)
{
  RUN_TEST_CASE(Arduino, pinMode);
  RUN_TEST_CASE(Arduino, digitalWrite);
  RUN_TEST_CASE(Arduino, digitalRead);
  RUN_TEST_CASE(Arduino, millis);
}

TEST_GROUP_RUNNER(ShregDriver)
{
  RUN_TEST_CASE(ShregDriver, shreg_init_input);
  RUN_TEST_CASE(ShregDriver, shreg_init_output);
  RUN_TEST_CASE(ShregDriver, shreg_read);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Init);
  RUN_TEST_GROUP(EmptyContext);
  RUN_TEST_GROUP(NonEmptyContext);
  RUN_TEST_GROUP(Misc);
  RUN_TEST_GROUP(Arduino);
  RUN_TEST_GROUP(ShregDriver);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}
