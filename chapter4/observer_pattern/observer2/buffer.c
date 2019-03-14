#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffer.h"

bool invoke_buffer_processor(BufferContext *object){
  bool ret = object->processor(object);
  free(object->pBuf);
  return ret;
}

int *allocate_buffer(BufferContext *pBufCtx, size_t size){
  // ここでNULLでなかったら再確保したい。あとでそれをオブザーバーパターンで通知できるようにしよう
  assert(pBufCtx->pBuf == NULL);
  pBufCtx->pBuf = (int *)malloc(sizeof(int) * size);
  pBufCtx->cnt = size;
  return pBufCtx->pBuf;
}
