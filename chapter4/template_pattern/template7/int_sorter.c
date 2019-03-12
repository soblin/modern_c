#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "buffer.h"
#include "file.h"
#include "int_sorter.h"

static bool do_with_buffer(BufferContext *p);
static bool reader(FileContext *p);
static bool writer(FileContext *p);
static int comparator(const void *p1, const void *p2);
static long file_size(FileContext *self);
static long file_current_pos(FileContext *pFileCtx);
static int set_file_pos(FileContext *pFileCtx, long offset, int whence);
static void file_error(Context *ctx);

typedef struct{
  BufferContext base;
  Context *pInputCtx;
  Context *pOutputCtx;
} MyBufferContext;

typedef struct{
  FileContext base;
  MyBufferContext *pBufCtx;
} MyFileContext;

IntSorterError int_sorter(const char *pInputFname, const char *pOutputFname){
  Context inputCtx = {pInputFname, ERR_OK};
  Context outputCtx = {pOutputFname, ERR_OK};

  MyBufferContext bufCtx = {{NULL, 0, do_with_buffer}, &inputCtx, &outputCtx};
  invoke_buffer_processor(&bufCtx.base);
  return outputCtx.errorCategory;
}

static bool do_with_buffer(BufferContext *p){
  MyBufferContext *pBufCtx = (MyBufferContext *)p;
  MyFileContext readFileCtx = {{NULL, pBufCtx->pInputCtx->pFname, "rb", reader}, pBufCtx};

  if(!invoke_file_processor(&readFileCtx.base)){
    file_error(pBufCtx->pInputCtx);
    return false;
  }

  qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);

  MyFileContext writerFileCtx = {{NULL, pBufCtx->pOutputCtx->pFname, "wb", writer}, pBufCtx};
  if(!invoke_file_processor(&writerFileCtx.base)){
    file_error(pBufCtx->pOutputCtx);
    return false;
  }

  return true;
}

static bool reader(FileContext *p){
  MyFileContext *pFileCtx = (MyFileContext *)p;
  MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

  long size = file_size(p);
  if(size == -1){
    file_error(pBufCtx->pInputCtx);
  }

  if(!allocate_buffer(&pBufCtx->base, size)){
    pBufCtx->pInputCtx->errorCategory = ERR_MEMORY;
    return false;
  }

  FILE *fp = get_file_pointer(p);
  if(pBufCtx->base.size != fread(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp)){
    file_error(pBufCtx->pInputCtx);
    return false;
  }

  return true;
}

static bool writer(FileContext *p){
  MyFileContext *pFileCtx = (MyFileContext *)p;
  MyBufferContext *pBufCtx = pFileCtx->pBufCtx;

  FILE *fp = get_file_pointer(p);
  if(fwrite(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp) != pBufCtx->base.size){
    file_error(pBufCtx->pOutputCtx);
    return false;
  }

  return true;
}

static int comparator(const void *p1, const void *p2){
  int i1 = *(const int *)p1;
  int i2 = *(const int *)p2;
  if(i1 > i2) return 1;
  else if(i1 < i2) return -1;
  else return 0;
}

static long file_size(FileContext *self){
  // 現在の位置を得る
  long save = file_current_pos(self);
  if(save < 0) return -1;

  // 一旦終わりにまで移動
  if(set_file_pos(self, 0, SEEK_END) != 0) return -1;

  // サイズを得る
  long size = file_current_pos(self);

  // 元の位置に戻す
  if(set_file_pos(self, save, SEEK_SET) != 0) return -1;

  return size;
}

// 現在の読んでいる位置を得る
static long file_current_pos(FileContext *pFileCtx){
  assert(pFileCtx);
  FILE *fp = get_file_pointer(pFileCtx);
  if(fp == NULL) return -1;

  return ftell(fp);
}

// whenceからoffsetの位置までfseekする
static int set_file_pos(FileContext *pFileCtx, long offset, int whence){
  assert(pFileCtx);
  FILE *fp = get_file_pointer(pFileCtx);
  if(fp == NULL) return -1;

  return fseek(fp, offset, whence);
}

static void file_error(Context *ctx){
  fprintf(stderr, "%s: %s\n", ctx->pFname, strerror(errno));
  ctx->errorCategory = ERR_FILE;
}
