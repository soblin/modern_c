#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "int_sorter.h"
#include "file.h"
#include "buffer.h"

static void do_with_buffer(BufferContext *self);
static int file_size(const char *pInputName);
static void size_reader(FileContext *self, FILE *fp);
static void file_error(Context *pCtx);
static void reader(FileContext *self, FILE *fp);
static int comparator(const void *p1, const void *p2);
static void writer(FileContext *self, FILE *fp);

typedef struct {
  FileContext base;
  int size;
} SizeGetterContext;

typedef struct {
  BufferContext base;
  Context *pInputCtx;
  Context *pOutputCtx;
} MyBufferContext;

typedef struct{
  FileContext base;
  MyBufferContext *pBufCtx;
} MyFileContext;

IntSorterError int_sorter(const char *pInputName, const char *pOutputName){
  Context readSizeCtx = {pInputName, ERR_OK};
  int size = file_size(pInputName);
  if(size == -1){
    file_error(&readSizeCtx);
    return ERR_FILE;
  }

  Context inputCtx = {pInputName, ERR_OK};
  Context outputCtx = {pOutputName, ERR_OK};
  MyBufferContext bufCtx = {{NULL, size, do_with_buffer}, &inputCtx, &outputCtx};
  if(!invoke_buffer_processor(&bufCtx.base)){
    return ERR_MEMORY;
  }

  return ERR_OK;
}

static void do_with_buffer(BufferContext *pCtx){
  MyBufferContext *p = (MyBufferContext *)(pCtx);
  MyFileContext readFileCtx = {{p->pInputCtx->pFname, "r", reader}, p};
  if(!invoke_file_processor(&readFileCtx.base)){
    file_error(p->pInputCtx);
    return;
  }

  qsort(pCtx->pBuf, pCtx->size, sizeof(int), comparator);

  MyFileContext writeFileCtx = {{p->pOutputCtx->pFname, "w", writer}, p};
  if(!invoke_file_processor(&writeFileCtx.base)){
    file_error(p->pOutputCtx);
    return;
  }
}

static int file_size(const char *pInputName){
  SizeGetterContext ctx = {{pInputName, "r", size_reader}, 0};
  if(!invoke_file_processor(&ctx.base)) return -1;

  return ctx.size;
}

static void size_reader(FileContext *self, FILE *fp){
  SizeGetterContext *p = (SizeGetterContext *)self;
  p->size = -1;
  int cnt = 0;
  char buf[32];
  while(fgets(buf, sizeof(buf), fp) != NULL){
    cnt++;
  }
  p->size = cnt;
}

static void file_error(Context *pCtx){
  fprintf(stderr, "%s: %s\n", pCtx->pFname, strerror(errno));
  pCtx->errorCategory = ERR_FILE;
}

static void reader(FileContext *self, FILE *fp){
  MyFileContext *pFileCtx = (MyFileContext *)self;
  BufferContext *pBufCtx = (BufferContext *)(pFileCtx->pBufCtx);
  int cnt = 0;
  char buf[32];
  while(fgets(buf, sizeof(buf), fp) != NULL && cnt < pBufCtx->size){
    int val = atoi(buf);
    pBufCtx->pBuf[cnt] = val;
    cnt++;
  }
}

static void writer(FileContext *self, FILE *fp){
  MyFileContext *pFileCtx = (MyFileContext *)self;
  BufferContext *pBufCtx = (BufferContext *)(pFileCtx->pBufCtx);
  for(int i=0; i<pBufCtx->size; ++i){
    fprintf(fp, "%d\n", pBufCtx->pBuf[i]);
  }
}

static int comparator(const void *p1, const void *p2){
  int i1 = *(const int*)(p1);
  int i2 = *(const int*)(p2);
  if(i1 > i2) return 1;
  else if(i1 < i2) return -1;
  else return 0;
}
