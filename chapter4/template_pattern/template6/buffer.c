#include <stdlib.h>
#include "buffer.h"

bool invoke_buffer_processor(BufferContext *self){
  self->pBuf = (int*)malloc(sizeof(int) * self->size);
  if(self->pBuf == NULL) return false;
  self->processor(self);
  free(self->pBuf);
  return true;
}
