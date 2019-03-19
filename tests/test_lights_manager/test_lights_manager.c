#include "unity_fixture.h"

TEST_GROUP_RUNNER(NonFlashing)
{
  RUN_TEST_CASE(NonFlashing, LmInitTurnsAllLightsOff);
  RUN_TEST_CASE(NonFlashing, LmUpdateWithoutProgrammingDoesNotChangeState);
  RUN_TEST_CASE(NonFlashing, ProgrammingLightOnDoesNotChangeState);
  RUN_TEST_CASE(NonFlashing, TurnOnOneLightWithLowestNumber);
  RUN_TEST_CASE(NonFlashing, TurnOnOneLightWithHighestNumber);
  RUN_TEST_CASE(NonFlashing, UpdateTwiceAfterProgrammingOnChangesStateOnce);
  RUN_TEST_CASE(NonFlashing, UpdateAfterProgrammingOnAndInitDoesNotChangeState);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(NonFlashing);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}

