#ifndef INT_SORTER_H_
#define INT_SORTER_H_

typedef enum {
  ERR_CAT_OK = 0,
  ERR_CAT_FILE,
  ERR_CAT_MEMORY
} IntSorterError;

typedef struct {
  const char *pFname;
  int errorCategory;
} Context;

IntSorterError int_sorter(const char *pInputFile, const char *pOutputFile);
#endif
