#include "file.h"

bool invoke_file_processor(FileContext *object){
  FILE *fp = fopen(object->pFname, object->pMode);
  if(fp == NULL) return false;

  object->processor(object, fp);
  return true;
}
