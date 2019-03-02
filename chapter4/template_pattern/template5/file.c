#include "file.h"

bool invoke_file_processor(FileAccessorContext *ctx){
  FILE *fp = fopen(ctx->pFname, ctx->pMode);
  if(fp == NULL) return false;
  ctx->processor(ctx, fp);
  fclose(fp);
  return true;
}
