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
  int size;
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

static bool do_with_buffer(BufferContext *object){
  MyBufferContext *pBufCtx = (MyBufferContext *)object;
  void *observer_table[4];
  MyFileAccessorContext readFileCtx = {
    {NULL, pBufCtx->pAppCtx->pFname, "r", new_array_list(observer_table), reader}, pBufCtx
  };
  add_file_error_observer(&readFileCtx.base, &file_error_observer);

  if(!invoke_file_processor(&readFileCtx.base)) return false;

  qsort(object->pBuf, object->size, sizeof(int), comparator);

  MyFileAccessorContext writeFileCtx = {
    {NULL, pBufCtx->pAppCtx->pFname, "w", new_array_list(observer_table), writer}, pBufCtx
  };

  add_file_error_observer(&writeFileCtx.base, &file_error_observer);
  
  return invoke_file_processor(&writeFileCtx.base);
}

static bool reader(FileAccessorContext *object){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)object;

  int size = file_size(object);
  if(size <= 0) return false;

  if(!allocate(&pFileCtx->pBufCtx->base, size)){
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
  if(i1 > i2)      return 1;
  else if(i1 < i2) return -1;
  else             return 0;
}

static void file_error(FileErrorObserver *object, FileAccessorContext *pFileCtx){
  fprintf(stderr, "File access error: '%s'(mode: %s): %s\n",
          pFileCtx->pFname, pFileCtx->pMode, strerror(errno));

  MyFileAccessorContext *pMyFileCtx = (MyFileAccessorContext *)pFileCtx;
  pMyFileCtx->pBufCtx->pAppCtx->errorCategory = ERR_FILE;
}
