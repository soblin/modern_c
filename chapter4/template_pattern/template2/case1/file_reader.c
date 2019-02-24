#include "file_reader.h"

bool read_file(FileReaderContext *pFileCtx){
  FILE *fp = fopen(pFileCtx->pFname, "r");
  if(fp == NULL) return false;
  pFileCtx->processor(pFileCtx, fp);
  fclose(fp);
  return true;
}

