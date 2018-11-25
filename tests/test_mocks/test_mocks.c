#include "unity_fixture.h"

static void RunAllTests(void)
{
  TEST_ONLY();
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}
