#ifndef FILE_ACCESSOR_H_
#define FILE_ACCESSOR_H_

#include <stdbool.h>
#include <stdio.h>

#include "buffer.h"
#include "array_list.h"

struct FileAccessorContext;

typedef struct FileErrorObserver{
  void (*const onError)(struct FileErrorObserver *self, struct FileAccessorContext *pFileCtx);
} FileErrorObserver;

extern FileErrorObserver default_file_error_observer;

typedef struct FileAccessorContext{
  FILE *fp;
  const char *pFname;
  const char *pMode;
  ArrayList observer_table;

  bool (*const processor)(struct FileAccessorContext *self);
} FileAccessorContext;

bool invoke_file_processor(FileAccessorContext *object);
FILE *get_file_pointer(FileAccessorContext *object);
int file_size(FileAccessorContext *object);
bool read_file(FileAccessorContext *object, BufferContext *pBufferContext);
bool write_file(FileAccessorContext *object, BufferContext *pBufferContext);
void add_file_error_observer(FileAccessorContext *object, FileErrorObserver *pErrorObserver);
void remove_file_error_observer(FileAccessorContext *object, FileErrorObserver *pErrorObserver);

#endif
