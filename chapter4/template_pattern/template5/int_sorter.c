#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "int_sorter.h"
#include "file.h"
#include "buffer.h"

static long file_size(const char *pInputName);
static void size_reader(FileAccessorContext *pCtx, FILE *fp);
static void do_with_buffer(BufferContext *pCtx);
static void file_error(Context *pCtx);
static void writer(FileAccessorContext *pCtx, FILE *fp);
static void reader(FileAccessorContext *pCtx, FILE *fp);
static int comparator(const void *p1, const void *p2);

typedef struct {
  FileAccessorContext base;
  long size;
} SizeGetterContext;

typedef struct {
  BufferContext base;
  Context *pInputCtx;
  Context *pOutputCtx;
} MyBufferContext;

typedef struct {
  FileAccessorContext base;
  MyBufferContext *pBufCtx;
} MyFileAccessorContext;

IntSorterError int_sorter(const char *pInputName, const char *pOutputName){
  Context readSizeCtx = {pInputName, ERR_CAT_OK};

  long size = file_size(pInputName);
  if(size == -1){
    file_error(&readSizeCtx);
    return ERR_CAT_FILE;
  }
  
  Context inputCtx = {pInputName, ERR_CAT_OK};
  Context outputCtx = {pOutputName, ERR_CAT_OK};
  MyBufferContext bufCtx = {{NULL, size, do_with_buffer}, &inputCtx, &outputCtx};
  if(!invoke_buffer_processor(&bufCtx.base)){
    return ERR_CAT_MEMORY;
  }

  return ERR_CAT_OK;
}

static long file_size(const char *pInputName){
  SizeGetterContext ctx = {{pInputName, "r", size_reader}, 0};
  if(!invoke_file_processor(&ctx.base))
    return -1;

  return ctx.size;
}

// MyBufferContextのprocessのメンバ関数
// この関数の前後に pCtx のメモリ確保が挟まっている
static void do_with_buffer(BufferContext *pCtx){
  MyBufferContext *p = (MyBufferContext *)pCtx;
  MyFileAccessorContext readFileCtx = {{p->pInputCtx->pFname, "r", reader}, p};
  // バッファはこの関数がinvokeされている時点ですでにpCtxに確保されている
  // invoke reader and load the file context into buffer
  if(!invoke_file_processor(&readFileCtx.base)){
    file_error(p->pInputCtx);
    return;
  }

  qsort(pCtx->pBuf, pCtx->size / sizeof(int), sizeof(int), comparator);
  
  MyFileAccessorContext writeFileCtx = {{p->pOutputCtx->pFname, "w", writer}, p};
  // invoke write and write buffer comparator
  if(!invoke_file_processor(&writeFileCtx.base)){
    file_error(p->pOutputCtx);
    return;
  }
}
static void size_reader(FileAccessorContext *pCtx, FILE *fp){
  SizeGetterContext *p = (SizeGetterContext *)pCtx;
  p->size = -1;
  if(fseek(fp, 0, SEEK_END) == 0)
    p->size = ftell(fp);
}

static void file_error(Context *pCtx){
  fprintf(stderr, "%s: %s\n", pCtx->pFname, strerror(errno));
  pCtx->errorCategory = ERR_CAT_FILE;
}

static void reader(FileAccessorContext *p, FILE *fp){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
  MyBufferContext *pBufCtx = (pFileCtx->pBufCtx);
  int read_size = fread(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp);
  if(read_size != pBufCtx->base.size){
    file_error(pBufCtx->pInputCtx);
  }
}

static void writer(FileAccessorContext *p, FILE *fp){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
  MyBufferContext *pBufCtx = pFileCtx->pBufCtx;
  int write_size = fwrite(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp);
  if(write_size != pBufCtx->base.size){
    file_error(pBufCtx->pOutputCtx);
  }
}

static int comparator(const void *p1, const void *p2){
  int i1 = *(const int *)(p1);
  int i2 = *(const int *)(p2);
  if(i1 > i2) return 1;
  else if(i1 < i2) return -1;
  else return 0;
}
