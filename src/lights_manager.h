#ifndef LIGHTS_MANAGER_H
#define LIGHTS_MANAGER_H

#include <stdint.h>

#define LM_PIN_LATCH                  (2)
#define LM_PIN_CLOCK                  (3)
#define LM_PIN_DATA                   (4)
#define LM_BUFFER_SIZE                (4)
#define LM_MAX_NUMBER_OF_LIGHTS       (LM_BUFFER_SIZE * 8)


void
lm_init (void);

void
lm_update (void);

void
lm_on (uint8_t light);

#endif /* LIGHTS_MANAGER_H */

