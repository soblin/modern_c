#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileContext {
  const char *pFname;
  const char *pMode;
  // FileContextはファイル名だけを保持する
  // FILEポインタとしてはfile_processorで開いたものを用いるので引数として与える(メンバにしない)
  void (*processor)(struct FileContext *self, FILE *fp);
} FileContext;

// processorをinvokeする
bool invoke_file_processor(FileContext *object);

#endif
