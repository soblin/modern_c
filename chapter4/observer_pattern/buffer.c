#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffer.h"

bool invoke_buffer_processor(BufferContext *object){
  bool ret = object->processor(object);
  free(object->pBuf);
  return ret;
}

void *allocate_buffer(BufferContext *pBufCtx, size_t size){
  assert(pBufCtx->pBuf == NULL);
  pBufCtx->pBuf = malloc(size);
  pBufCtx->size = size;
  return pBufCtx->pBuf;
}
