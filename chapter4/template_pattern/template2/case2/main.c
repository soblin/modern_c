#include <limits.h>
#include <stdlib.h>
#include "file_reader.h"

typedef struct IntFileReaderContext {
  FileReaderContext base;
  int result;
} IntFileReaderContext;

static int calc_range(FILE *fp){
  int min = INT_MAX;
  int max = INT_MIN;
  char buf[256];

  while((fgets(buf, sizeof(buf), fp) != NULL)){
    if(buf[0] == '\n') return -1;
    int value = atoi(buf);
    min = (min > value)? value : min;
    max = (max < value)? value : max;
  }
  return (max - min);
}

void process_impl(FileReaderContext *self, FILE *fp){
  IntFileReaderContext *pCtx = (IntFileReaderContext *)(self);
  pCtx->result = calc_range(fp);
}

int range(const char *pFname){
  IntFileReaderContext ctx = {{pFname, process_impl}, 0};
  // process_impl(processor)がthisポインタを持つので、ctx.resultに結果が返ってくる
  bool success = process_file(&ctx.base);
  if(!success) return -1;
  return ctx.result;
}

int main(){
  const char filename[] = "toydata.txt";
  // このfileに対して操作を行いたい
  int ret = range(filename);
  printf("result is %d\n", ret);
  return 0;
}
