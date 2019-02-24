#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileReaderContext{
  const char *pFname;
  void (*const processor)(struct FileReaderContext *self, FILE *fp);
} FileReaderContext;

// ファイル読み込み失敗したらfalse, うまくいってprocessしたらtrue
bool read_file(FileReaderContext *pFileCtx);

#endif
