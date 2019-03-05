#include "unity_fixture.h"

TEST_GROUP_RUNNER(NonFlashing)
{
  RUN_TEST_CASE(NonFlashing, LmInitTurnsAllLightsOff);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(NonFlashing);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}

