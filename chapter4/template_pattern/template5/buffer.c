#include <stdlib.h>
#include "buffer.h"

bool invoke_buffer_processor(BufferContext *ctx){
  ctx->pBuf = malloc(ctx->size);
  if(ctx->pBuf == NULL) return false;
  ctx->processer(ctx);
  free(ctx->pBuf);
  return true;
}
