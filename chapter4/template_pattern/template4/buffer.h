#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext {
  void *pBuf;
  size_t size;
  void (*process)(struct BufferContext *self);
} BufferContext;

// processを呼び出す
// pBufにバッファーを確保して何か処理をし、成功したらfreeしてtrueを返す
bool buffer(BufferContext *pCtx);

#endif
