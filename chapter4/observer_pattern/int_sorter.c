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
  Context *pAppCtx;
} MyBufferContext;

typedef struct{
  FileAccessorContext base;
  MyBufferContext *pBufCtx;
} MyFileAccessorContext;

typedef struct{
  FileAccessorContext base;
  long size;
} SizeGetterContext;

static FileErrorObserver file_error_observer = {
  file_error
};

IntSorterError int_sorter(const char *pFname){
  Context ctx = {pFname, NULL, NULL, ERR_OK};

  MyBufferContext bufCtx = {{NULL, 0, do_with_buffer}, &ctx};
  invoke_buffer_processor(&bufCtx.base);
  return ctx.errorCategory;
}

static bool do_with_buffer(BufferContext *p){
  MyBufferContext *pBufCtx = (MyBufferContext *)p;
  MyFileAccessorContext readFileCtx = {
    {NULL, pBufCtx->pAppCtx->pFname, "rb", reader, &file_error_observer},
    pBufCtx
  };

  if(!invoke_file_processor(&readFileCtx.base)) return false;

  qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

  MyFileAccessorContext writeFileCtx = {
    {NULL, pBufCtx->pAppCtx->pFname, "wb", writer, &file_error_observer},
    pBufCtx
  };

  return invoke_file_processor(&writeFileCtx.base);
}

static bool reader(FileAccessorContext *object){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)object;

  long size = file_size(object);
  if(size == -1) return false;

  if(!allocate_buffer(&pFileCtx->pBufCtx->base, size)){
    pFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_MEMORY;
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
  default_file_error_observer.onError(object, pFileCtx);

  MyFileAccessorContext *pMyFileCtx = (MyFileAccessorContext *)pFileCtx;
  pMyFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_FILE;
}
