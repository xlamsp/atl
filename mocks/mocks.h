#ifndef MOCKS_H
#define MOCKS_H

#define MOCKS_MAX_EXPECTATIONS_NUMBER   (16)
#define MOCKS_MAX_CONTEXT_DATA_SIZE     (256)

typedef enum {
  mocks_success,
  mocks_not_initialized,
  mocks_no_more_expectations,
  mocks_not_all_expectations_used,
  mocks_not_matching_id,
  mocks_no_room_for_expectation,
  mocks_invalid_ctx_size,
  mocks_invalid_ctx,
  mocks_ctx_size_mismatch,
  mocks_no_room_for_ctx_data,
} mocks_return_code;

/*
 * mocks_init
 */
void
mocks_init(void);

/*
 * mocks_expect
 *
 *  id - identifier of the interface expected to call
 *  ctx - context of the expected call
 *  size - size of the context
 *
 *  return - operation status code
 */
mocks_return_code
mocks_expect(int id, void *ctx, int size);

/*
 * mocks_invoke
 *
 *  id - identifier of the interface being invoked
 *  ctx - context of the interface being invoked
 *  size - size of the context
 *
 *  return - operation status code
 */
mocks_return_code
mocks_invoke(int id, void *ctx, int size);

/*
 * mocks_verify
 *
 *  return - operation status code
 */
mocks_return_code
mocks_verify(void);

#endif /* MOCKS_H */

