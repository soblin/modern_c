#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileAccessorContext {
  const char *pFname;
  const char *pMode;
  void (*processor)(struct FileAccessorContext *self, FILE *fp);
} FileAccessorContext;

bool invoke_file_processor(FileAccessorContext *ctx);
#endif
