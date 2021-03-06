#include "unity_fixture.h"

TEST_GROUP_RUNNER(Input)
{
  RUN_TEST_CASE(Input, InitPinsSingleChain);
  RUN_TEST_CASE(Input, InitPinsMultipleChains);
  RUN_TEST_CASE(Input, ReadSingleChipChain);
  RUN_TEST_CASE(Input, ReadArbitraryValueSingleChipChain);
  RUN_TEST_CASE(Input, ReadArbitraryValuesFromMultipleSingleChipChains);
  RUN_TEST_CASE(Input, ReadArbitraryDataFromMultipleChipChain);
}

TEST_GROUP_RUNNER(Output)
{
  RUN_TEST_CASE(Output, InitPinsSingleChain);
  RUN_TEST_CASE(Output, InitPinsMultipleChains);
  RUN_TEST_CASE(Output, WriteSingleChipChain);
  RUN_TEST_CASE(Output, WriteArbitraryValueSingleChipChain);
  RUN_TEST_CASE(Output, WriteArbitraryValuesToMultipleSingleChipChains);
  RUN_TEST_CASE(Output, WriteArbitraryDataToMultipleChipChain);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(Input);
  RUN_TEST_GROUP(Output);
}

int main(int argc, const char **argv)
{
  return UnityMain(argc, argv, RunAllTests);
}

