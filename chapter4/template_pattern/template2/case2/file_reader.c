#include "file_reader.h"

bool process_file(FileReaderContext *pCtx){
  FILE *fp = fopen(pCtx->pFname, "r");
  if(fp == NULL) return false;
  pCtx->process(pCtx, fp);
  return true;
}
