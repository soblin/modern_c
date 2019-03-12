#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext{
  // template <class ReSourceType> BufferContext
  // ResourceType -> int みたいにもできそう。
  void *pBuf;
  size_t size;
  bool (*processor)(struct BufferContext *p);
} BufferContext;

bool invoke_buffer_processor(BufferContext *self);
void *allocate_buffer(BufferContext *self, size_t size);

#endif
