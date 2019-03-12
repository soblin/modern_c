#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext{
  int *pBuf;
  size_t size;
  void (*processor)(struct BufferContext *self);
} BufferContext;

bool invoke_buffer_processor(BufferContext *self);

#endif
