#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext{
  int *pBuf;
  size_t cnt;
  bool (*const processor)(struct BufferContext *self);
} BufferContext;

bool invoke_buffer_processor(BufferContext *object);
int *allocate_buffer(BufferContext *object, size_t size);

#endif
