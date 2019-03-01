#include <stdlib.h>
#include "buffer.h"

bool buffer(BufferContext *pCtx){
  pCtx->pBuf = malloc(pCtx->size);
  if(pCtx->pBuf == NULL) return false;
  pCtx->process(pCtx);
  free(pCtx->pBuf);
  return true;
}
