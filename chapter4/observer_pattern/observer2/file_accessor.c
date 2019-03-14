#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

#include "file_accessor.h"

static void default_file_error_handler(FileErrorObserver *object, FileAccessorContext *pFileCtx);

FileErrorObserver g_default_file_error_observer = {
  &default_file_error_handler
};

bool invoke_file_processor(FileAccessorContext *object){
  assert(object);

  if(object->pFileErrorObserver == NULL){
    object->pFileErrorObserver = &g_default_file_error_observer;
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

int file_size(FileAccessorContext *object){
  FILE *fp = get_file_pointer(object);
  int cnt = 0;
  char buf[32];
  while(fgets(buf, sizeof(buf), fp) != NULL){
    cnt++;
  }
  printf("%d\n", cnt);
  //object->fp = NULL;
  fseek(fp, 0, SEEK_SET);
  return cnt;
}

bool read_file(FileAccessorContext *object, BufferContext *pBufCtx){
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return false;

  int cnt = 0;
  char buf[32];
  while(fgets(buf, sizeof(buf), fp) != NULL){
    pBufCtx->pBuf[cnt] = atoi(buf);
    cnt++;
  }
  if(pBufCtx->cnt != cnt){
    object->pFileErrorObserver->onError(object->pFileErrorObserver, object);
  }
  return true;
}

bool write_file(FileAccessorContext *object, BufferContext *pBufCtx){
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return false;

  for(int i=0; i<pBufCtx->cnt; ++i){
    fprintf(fp, "%d\n", pBufCtx->pBuf[i]);
  }

  return true;
}

static void default_file_error_handler(FileErrorObserver *object, FileAccessorContext *pFileCtx){
  fprintf(stderr, "File access error: '%s'(mode: %s): %s\n",
          pFileCtx->pFname, pFileCtx->pMode, strerror(errno));
}
