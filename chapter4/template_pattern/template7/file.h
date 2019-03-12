#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileContext{
  FILE *fp;
  const char *pFname;
  const char *pMode;
  bool (*processor)(struct FileContext *self);
} FileContext;

bool invoke_file_processor(FileContext *self);
FILE *get_file_pointer(FileContext *self);

#define NEW_FILE(pFname, pMode, processor){ NULL, (pFname), (pMode), (processor)}

#endif
