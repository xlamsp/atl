#ifndef MOCKS_H
#define MOCKS_H

typedef enum {
  mocks_not_initialized,
} mocks_return_code;

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

