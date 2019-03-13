#ifndef FILE_ACCESSOR_H_
#define FILE_ACCESSOR_H_

#include <stdbool.h>
#include <stdio.h>

#include "buffer.h"

struct FileAccessorContext;

typedef struct FileErrorObserver{
  void (*onError)(struct FileErrorObserver *self, struct FileAccessorContext *pFileCtx);
} FileErrorObserver;

extern FileErrorObserver default_file_error_observer;

typedef struct FileAccessorContext{
  FILE *fp;
  const char *pFname;
  const char *pMode;
  bool (*processor)(struct FileAccessorContext *self);
  FileErrorObserver *pFileErrorObserver;
} FileAccessorContext;

bool invoke_file_processor(FileAccessorContext *object);
FILE *get_file_pointer(FileAccessorContext *object);
long file_size(FileAccessorContext *object);
long file_current_pos(FileAccessorContext *object);
int set_file_pos(FileAccessorContext *object, long offset, int whence);
bool read_file(FileAccessorContext *object, BufferContext *pBufCtx);
bool write_file(FileAccessorContext *object, BufferContext *pBufCtx);

#endif
