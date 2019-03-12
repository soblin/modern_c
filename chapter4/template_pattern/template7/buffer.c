#include <assert.h>
#include <stdlib.h>
#include "buffer.h"

bool invoke_buffer_processor(BufferContext *self){
  assert(self);
  bool ret = self->processor(self);
  free(self->pBuf);
  return ret;
}

void *allocate_buffer(BufferContext *self, size_t size){
  assert(self);
  assert(self->pBuf == NULL);
  self->pBuf = malloc(size);
  self->size = size;
  return self->pBuf;
}
