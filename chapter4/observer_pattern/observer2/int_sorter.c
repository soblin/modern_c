#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static bool reader(FileAccessorContext *object);
static bool do_with_buffer(BufferContext *object);
static bool writer(FileAccessorContext *object);
static int comparator(const void *p1, const void *p2);
static void file_error(FileErrorObserver *object, FileAccessorContext *pFileCtx);

typedef struct{
  BufferContext base;
  Context *pInputCtx;
  Context *pOutputCtx;
} MyBufferContext;

typedef struct{
  FileAccessorContext base;
  MyBufferContext *pBufCtx;
} MyFileAccessorContext;

typedef struct{
  FileAccessorContext base;
  int cnt;
} SizeGetterContext;

static FileErrorObserver file_error_observer = {
  file_error
};

IntSorterError int_sorter(const char *pInputFname, const char *pOutputFname){
  Context inputCtx = {pInputFname, ERR_OK};
  Context outputCtx = {pOutputFname, ERR_OK};

  MyBufferContext bufCtx = {{NULL, 0, do_with_buffer}, &inputCtx, &outputCtx};

  invoke_buffer_processor(&bufCtx.base);

  return outputCtx.errorCategory;
}

static bool do_with_buffer(BufferContext *object){
  MyBufferContext *pBufCtx = (MyBufferContext *)object;
  MyFileAccessorContext readFileCtx = {
    {NULL, pBufCtx->pInputCtx->pFname, "r", reader}, pBufCtx
  };

  if(!invoke_file_processor(&readFileCtx.base)) return false;

  qsort(object->pBuf, object->cnt, sizeof(int), comparator);

  MyFileAccessorContext writeFileCtx = {
    {NULL, pBufCtx->pOutputCtx->pFname, "w", writer}, pBufCtx
  };

  return invoke_file_processor(&writeFileCtx.base);
}

static bool reader(FileAccessorContext *object){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)object;

  int cnt = file_size(object);
  if(cnt == -1) return false;

  if(!allocate_buffer(&pFileCtx->pBufCtx->base, cnt)){
    pFileCtx->pBufCtx->pInputCtx->errorCategory = ERR_MEMORY;
    return false;
  }

  return read_file(object, &pFileCtx->pBufCtx->base);
}

static bool writer(FileAccessorContext *object){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)object;
  return write_file(object, &pFileCtx->pBufCtx->base);
}

static int comparator(const void *p1, const void *p2){
  int i1 = *(const int *)p1;
  int i2 = *(const int *)p2;

  if(i1 > i2) return 1;
  else if(i1 < i2) return -1;
  else return 0;
}

static void file_error(FileErrorObserver *object, FileAccessorContext *pFileCtx){
  g_default_file_error_observer.onError(object, pFileCtx);

  MyFileAccessorContext *pMyFileCtx = (MyFileAccessorContext *)pFileCtx;
  pMyFileCtx->pBufCtx->pInputCtx->errorCategory = ERR_FILE;
}
