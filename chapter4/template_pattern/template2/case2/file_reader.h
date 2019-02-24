#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct FileReaderContext {
  const char *pFname;
  void (*process)(struct FileReaderContext *self, FILE *fp);
  // ここで引数としてselfがなかったら、「作用を与えるオブジェクト」を指定できない
  // ので、この場合だと`result`に結果を保存できない
} FileReaderContext;

bool process_file(FileReaderContext *pCtx);
#endif
