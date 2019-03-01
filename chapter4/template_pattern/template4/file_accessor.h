#ifndef FILE_ACCESSOR_H_
#define FILE_ACCESSOR_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileAccessorContext {
  const char *pFname;
  const char *pMode;
  void (*process)(struct FileAccessorContext *self, FILE *fp);
} FileAccessorContext;

// processを呼び出す関数
// ただ単にファイルオープンと処理に成功したらtrueを返すということを規定するだけ
bool access_file(FileAccessorContext *pCtx);

#endif
