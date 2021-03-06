#ifndef TEST_LIGHTS_MANAGER_COMMON_H
#define TEST_LIGHTS_MANAGER_COMMON_H


#define LM_LIGHT_NUMBER_OUT_OF_RANGE  (LM_LIGHT_NUMBER_MAX + 1)


void
testLm_ProgramLightOn (uint8_t light);

void
testLm_ProgramLightOff (uint8_t light);

void
testLm_ExpectStateChange (void);

void
testLm_Expect_lm_init (uint32_t system_clock_at_init);

void
testLm_Expect_lm_update (uint32_t system_clock_at_update);

#endif /* TEST_LIGHTS_MANAGER_COMMON_H */

