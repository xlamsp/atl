#include "unity_fixture.h"

TEST_GROUP_RUNNER(Init)
{
  RUN_TEST_CASE(Init, ExpectPriorToInitFails);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Init);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}
