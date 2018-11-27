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
 */
mocks_return_code
mocks_expect(int id, void *ctx, int size);

#endif /* MOCKS_H */

