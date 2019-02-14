#ifndef MOCKS_SHREG_DRIVER_H
#define MOCKS_SHREG_DRIVER_H

#include "mocks.h"
#include "shreg_driver.h"

enum {
  mock_id_shreg_init_input = mocks_id_offset_shreg_driver,
  mock_id_shreg_init_output,
};

void
expect_shreg_init_input(shreg_driver_t *handle);

void
expect_shreg_init_output(shreg_driver_t *handle);

#endif /* MOCKS_SHREG_DRIVER_H */

