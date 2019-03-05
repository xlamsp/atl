#ifndef MOCKS_SHREG_DRIVER_H
#define MOCKS_SHREG_DRIVER_H

#include "mocks.h"
#include "shreg_driver.h"

enum {
  mock_id_shreg_init_input = mocks_id_offset_shreg_driver,
  mock_id_shreg_init_output,
  mock_id_shreg_read,
  mock_id_shreg_write,
};

#define MOCKS_SHREG_DRIVER_MAX_BUFFER_SIZE    (4)

void
expect_shreg_init_input(shreg_driver_t *handle);

void
expect_shreg_init_output(shreg_driver_t *handle);

void
expect_shreg_read(shreg_driver_t *handle, uint8_t *buffer);

void
expect_shreg_write(shreg_driver_t *handle, uint8_t *buffer);

#endif /* MOCKS_SHREG_DRIVER_H */

