#include "unity_fixture.h"

TEST_GROUP_RUNNER(Input)
{
  RUN_TEST_CASE(Input, InitPinsSingleChain);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Input);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}

