#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct BufferContext{
  // member variables
  int *pBuf;
  size_t size;
  // member function
  bool (*const processor)(struct BufferContext *self);
} BufferContext;

bool invoke_buffer_processor(BufferContext *object);
int *allocate(BufferContext *object, size_t size);

#endif
