#ifndef TEST_LIGHTS_MANAGER_COMMON_H
#define TEST_LIGHTS_MANAGER_COMMON_H

void
testLm_ProgramLightOn (uint8_t light);

void
testLm_ProgramLightOff (uint8_t light);

void
testLm_ExpectStateChange (void);

void
testLm_Expect_lm_init (void);

void
testLm_Expect_lm_update (uint32_t milliseconds);

#endif /* TEST_LIGHTS_MANAGER_COMMON_H */

