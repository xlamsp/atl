#ifndef LIGHTS_MANAGER_H
#define LIGHTS_MANAGER_H

#include "shreg_driver.h"

void
lm_init (void);

void
lm_update (void);

void
lm_on (uint8_t light);

#endif /* LIGHTS_MANAGER_H */

