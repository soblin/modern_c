#include <assert.h>
#include "file.h"

bool invoke_file_processor(FileContext *self){
  assert(self);
  bool ret = self->processor(self);
  if(self->fp != NULL){
    if(fclose(self->fp) != 0) ret = false;
  }
  return ret;
}

FILE *get_file_pointer(FileContext *self){
  assert(self);
  if(self->fp == NULL){
    self->fp = fopen(self->pFname, self->pMode);
  }
  return self->fp;
}
