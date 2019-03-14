#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "file_accessor.h"
#include "array_list.h"

static void file_error(FileAccessorContext *object);

bool invoke_file_processor(FileAccessorContext *object){
  assert(object);
  bool ret = object->processor(object);
  if(object->fp != NULL){
    if(fclose(object->fp) != 0){
      file_error(object);
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
      file_error(object);
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
  if(pBufCtx->size != cnt){
    file_error(object);
    return false;
  }

  return true;
}

bool write_file(FileAccessorContext *object, BufferContext *pBufCtx){
  FILE *fp = get_file_pointer(object);
  if(fp == NULL) return false;

  for(int i=0; i<pBufCtx->size; ++i){
    fprintf(fp, "%d\n", pBufCtx->pBuf[i]);
  }

  return true;
}

void add_file_error_observer(FileAccessorContext *object, FileErrorObserver *pErrorObserver){
  ArrayList *pTable = &(object->observer_table);
  pTable->add(pTable, pErrorObserver);
}

void remove_file_error_observer(FileAccessorContext *object, FileErrorObserver *pErrorObserver){
  ArrayList *pTable = &(object->observer_table);
  pTable->remove(pTable, pErrorObserver);
}

static void file_error(FileAccessorContext *object){
  ArrayList *pTable = &(object->observer_table);
  for(int i=0; i<pTable->index; ++i){
    FileErrorObserver *pObserver = pTable->get(pTable, i);
    pObserver->onError(pObserver, object);
  }
}
