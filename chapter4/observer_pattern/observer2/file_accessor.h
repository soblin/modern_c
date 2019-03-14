#ifndef FILE_ACCESSOR_H_
#define FILE_ACCESSOR_H_

#include <stdio.h>
#include <stdbool.h>

#include "buffer.h"

struct FileAccessorContext;

typedef struct FileErrorObserver{
  void (*const onError)(struct FileErrorObserver *self, struct FileAccessorContext *pFileCtx);
} FileErrorObserver;

extern FileErrorObserver g_default_file_error_observer;

typedef struct FileAccessorContext{
  FILE *fp;
  const char *pFname;
  const char *pMode;
  bool (*const processor)(struct FileAccessorContext *self);
  FileErrorObserver *pFileErrorObserver;
} FileAccessorContext;

bool invoke_file_processor(FileAccessorContext *object);
FILE *get_file_pointer(FileAccessorContext *object);
int file_size(FileAccessorContext *object);
bool read_file(FileAccessorContext *object, BufferContext *pBufCtx);
bool write_file(FileAccessorContext *object, BufferContext *pBufCtx);

#endif
