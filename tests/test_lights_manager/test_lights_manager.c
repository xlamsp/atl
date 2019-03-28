#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightsOn)
{
  RUN_TEST_CASE(LightsOn, LmUpdateWithoutProgrammingDoesNotChangeState);
  RUN_TEST_CASE(LightsOn, ProgrammingLightOnDoesNotChangeState);
  RUN_TEST_CASE(LightsOn, TurnOnOneLightWithLowestNumber);
  RUN_TEST_CASE(LightsOn, TurnOnOneLightWithHighestNumber);
  RUN_TEST_CASE(LightsOn, UpdateTwiceAfterProgrammingOnChangesStateOnce);
  RUN_TEST_CASE(LightsOn, UpdateAfterProgrammingOnAndInitDoesNotChangeState);
  RUN_TEST_CASE(LightsOn,
    UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState1);
  RUN_TEST_CASE(LightsOn, CanTurnOnMultipleLights);
  RUN_TEST_CASE(LightsOn,
    UpdateAfterProgrammingOnLightAlreadyOnDoesNotChangeState2);
  RUN_TEST_CASE(LightsOn, TurningOnLightWithNumberOutOfRangeDoesNothing);
}

TEST_GROUP_RUNNER(LightsOff)
{
  RUN_TEST_CASE(LightsOff, LmInitTurnsAllLightsOff);
  RUN_TEST_CASE(LightsOff, ProgrammingLightOffDoesNotChangeState);
  RUN_TEST_CASE(LightsOff, TurnOffOneLightWithLowestNumber);
  RUN_TEST_CASE(LightsOff, TurnOffOneLightWithHighestNumber);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(LightsOn);
  RUN_TEST_GROUP(LightsOff);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}

