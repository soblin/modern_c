#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext {
  void *pBuf;
  size_t size;
  void (*processer)(struct BufferContext *self);
} BufferContext;

bool invoke_buffer_processor(BufferContext *ctx);

#endif
