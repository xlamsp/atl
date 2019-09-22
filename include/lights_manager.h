#ifndef LIGHTS_MANAGER_H
#define LIGHTS_MANAGER_H

#include <stdint.h>

#define LM_PIN_LATCH                  (2)
#define LM_PIN_CLOCK                  (3)
#define LM_PIN_DATA                   (4)

#define LM_BUFFER_SIZE                (4)
#define LM_NUMBER_OF_LIGHTS           (LM_BUFFER_SIZE * 8)
#define LM_LIGHT_NUMBER_MIN           (0)
#define LM_LIGHT_NUMBER_MAX           (LM_NUMBER_OF_LIGHTS - 1)


void
lm_init (void);

void
lm_update (void);

void
lm_on (uint8_t light);

void
lm_off (uint8_t light);

void
lm_flash (uint8_t light);

#endif /* LIGHTS_MANAGER_H */

