#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <stdio.h>
int read_file(const char *pFname, int (*processor)(FILE *fp));

#endif
