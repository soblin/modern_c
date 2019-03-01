#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "int_sorter.h"
#include "file_accessor.h"
#include "buffer.h"

static void reader(FileAccessorContext *pCtx, FILE *fp);
static long file_size(const char *pFname);
static void size_reader(FileAccessorContext *pCtx, FILE *fp);
static void do_with_buffer(BufferContext *p);
static void writer(FileAccessorContext *pCtx, FILE *fp);
static int comparator(const void *p1, const void *p2);
static void file_error(Context *pCtx);

// FileAccessorContextを継承
typedef struct {
  FileAccessorContext base;
  long size;
} SizeGetterContext;

// BufferContextを継承
typedef struct {
  BufferContext base;
  Context *pAppCtx;
} MyBufferContext;

// 本丸
typedef struct {
  FileAccessorContext base;
  MyBufferContext *pBufCtx;
} MyFileAccessorContext;

static long file_size(const char *pFname){
  SizeGetterContext ctx = {{pFname, "r", size_reader}, 0};
  // access_fileはFileAccessorContextのprocessをinvokeする
  // この場合引数はSizeGetterContextなので、access_fileをinvokeするとsizeが得られているはず
  if(!access_file(&ctx.base))
    return -1;

  return ctx.size;
}

// あくまで処理がうまく行ったかを通知するだけ
IntSorterError int_sorter(const char *pFname){
  Context ctx = {pFname, ERR_CAT_OK};

  long size = file_size(pFname);
  if(size == -1){
    file_error(&ctx);
    return ctx.errorCategory;
  }

  // void *pBuf, long size, void (*)(BufferContext *)
  MyBufferContext bufCtx = {{NULL, size, do_with_buffer}, &ctx};
  if(!buffer(&bufCtx.base)){
    ctx.errorCategory = ERR_CAT_MEMORY;
  }
  return ctx.errorCategory;
}

// こいつはSizeGetterContextのメンバ関数になるので
// SizeGetterContext *にアップキャストするのは当たり前
// SizeGetterContextにsizeを通知する
static void size_reader(FileAccessorContext *pCtx, FILE *fp){
  SizeGetterContext *p = (SizeGetterContext *)(pCtx);
  p->size = -1;
  if(fseek(fp, 0, SEEK_END) == 0)
    p->size = ftell(fp);
}

static void do_with_buffer(BufferContext *p){
  MyBufferContext *pBufCtx = (MyBufferContext *)p;
  MyFileAccessorContext readFileCtx = {{pBufCtx->pAppCtx->pFname, "r", reader}, pBufCtx};
  // 読み込み(reader)を呼び出し
  if(!access_file(&readFileCtx.base)){
    file_error(pBufCtx->pAppCtx);
    return;
  }
  // 処理
  qsort(p->pBuf, p->size / sizeof(int), sizeof(int), comparator);
  // 書き込み(writer)呼び出し
  MyFileAccessorContext writeFileCtx = {{pBufCtx->pAppCtx->pFname, "w", writer}, pBufCtx};
  if(!access_file(&writeFileCtx.base)){
    file_error(pBufCtx->pAppCtx);
    return;
  }
}

// もちろんfpは開いている前提で使える
static void reader(FileAccessorContext *p, FILE *fp){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
  MyBufferContext *pBufCtx = pFileCtx->pBufCtx;
  // 予めサイズを取得している
  if(pBufCtx->base.size != fread(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp)){
    file_error(pBufCtx->pAppCtx);
  }
}

static void writer(FileAccessorContext *p, FILE *fp){
  MyFileAccessorContext *pFileCtx = (MyFileAccessorContext *)p;
  MyBufferContext *pBufCtx = pFileCtx->pBufCtx;
  if(fwrite(pBufCtx->base.pBuf, 1, pBufCtx->base.size, fp) != pBufCtx->base.size){
    file_error(pBufCtx->pAppCtx);
  }
}

static int comparator(const void *p1, const void *p2){
  int i1 = *(const int *)p1;
  int i2 = *(const int *)p2;
  if (i1 == i2) return 0;
  else if(i1 > i2) return 1;
  else return -1;
}

static void file_error(Context *pCtx){
  fprintf(stderr, "%s: %s\n", pCtx->pFname, strerror(errno));
  pCtx->errorCategory = ERR_CAT_FILE;
}
