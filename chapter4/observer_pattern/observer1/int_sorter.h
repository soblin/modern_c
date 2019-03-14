#ifndef INT_SORTER_H_
#define INT_SORTER_H_

#include "buffer.h"
#include "file_accessor.h"

typedef enum{
  ERR_OK = 0,
  ERR_FILE,
  ERR_MEMORY
} IntSorterError;

typedef struct{
  const char *pFname;
  int errorCategory;
} Context;

IntSorterError int_sorter(const char *pFname);

#endif
