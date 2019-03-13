#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext{
  void *pBuf;
  size_t size;
  bool (*processor)(struct BufferContext *self);
} BufferContext;

bool invoke_buffer_processor(BufferContext *object);
void *allocate_buffer(BufferContext *object, size_t size);

#endif
