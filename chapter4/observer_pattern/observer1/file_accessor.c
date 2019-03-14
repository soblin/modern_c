#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

#include "file_accessor.h"

static void default_file_error_handler(FileErrorObserver *object, FileAccessorContext *pFileCtx);

FileErrorObserver default_file_error_observer = {
  &default_file_error_handler
};

bool invoke_file_processor(FileAccessorContext *object){
  assert(object);
  if(object->pFileErrorObserver == NULL){
    object->pFileErrorObserver = &default_file_error_observer;
  }
  bool ret = object->processor(object);
  if(object->fp != NULL){
    if(fclose(object->fp) != 0){
      object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
      ret = false;
    }
  }
  return ret;
}

FILE *get_file_pointer(FileAccessorContext *object){
  assert(object);
  if(object->fp == NULL){
    object->fp = fopen(object->pFname, object->pMode);
    if(object->fp == NULL){
      object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
    }
  }

  return object->fp;
}

long file_size(FileAccessorContext *object){
  long save = file_current_pos(object);
  if(save < 0) return -1;

  if(set_file_pos(object, 0, SEEK_END) != 0) return -1;

  long size = file_current_pos(object);
  set_file_pos(object, save, SEEK_SET);

  return size;
}

long file_current_pos(FileAccessorContext *object){
  assert(object);
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return -1;

  long ret = ftell(fp);
  if(ret < 0) object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
  return ret;
}

int set_file_pos(FileAccessorContext *object, long offset, int whence){
  assert(object);
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return -1;

  int ret = fseek(fp, offset, whence);
  if(ret != 0) object->pFileErrorObserver->onError(object->pFileErrorObserver, object);

  return ret;
}

bool read_file(FileAccessorContext *object, BufferContext *pBufCtx){
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return false;

  if(pBufCtx->size != fread(pBufCtx->pBuf, 1, pBufCtx->size, fp)){
    object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
    return false;
  }

  return true;
}

bool write_file(FileAccessorContext *object, BufferContext *pBufCtx){
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return false;

  if(pBufCtx->size != fwrite(pBufCtx->pBuf, 1, pBufCtx->size, fp)){
    object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
    return false;
  }

  return true;
}

static void default_file_error_handler(FileErrorObserver *object, FileAccessorContext *pFileCtx){
  fprintf(stderr, "File access error '%s'(mode: %s): %s\n",
          pFileCtx->pFname, pFileCtx->pMode, strerror (errno));
}
