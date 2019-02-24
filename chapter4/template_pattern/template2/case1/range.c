#include <limits.h>
#include <stdlib.h>
#include "range.h"
#include "file_reader.h"

typedef struct {
  FileReaderContext base;
  int result;
} IntFileReaderContext;

static int int_processor_impl(FILE *fp){
  int min = INT_MAX;
  int max = INT_MIN;
  char buf[256];

  while((fgets(buf, sizeof(buf), fp)) != NULL){
    if(buf[0] == '\n') return -1;
    int value = atoi(buf);
    min = (min > value)? value : min;
    max = (max < value)? value : max;
  }

  return (max - min);
}

static void int_processor(FileReaderContext *self, FILE *fp){
  IntFileReaderContext *pCtx = (IntFileReaderContext *)(self);
  pCtx->result = int_processor_impl(fp);
}

int range(const char *pFname){
  IntFileReaderContext ctx = {{pFname, int_processor}, 0};
  // read_file関数はあくまでFileReaderContextとしてメモリを読むが
  // processorに登録されている関数int_processorはIntFileReaderContextとして
  // メモリ領域を読むので、resultにまで'extend'するイメージ
  bool result = read_file(&ctx.base);
  if(result == false) return -1;
  return ctx.result;
}
