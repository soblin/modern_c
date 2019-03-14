#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buffer.h"

bool invoke_buffer_processor(BufferContext *object){
  bool ret = object->processor(object);
  free(object->pBuf);
  return ret;
}
  
int *allocate(BufferContext *object, size_t size){
  assert(object->pBuf == NULL);
  object->pBuf = (int *)malloc(sizeof(int) * size);
  object->size = size;

  return object->pBuf;
}
