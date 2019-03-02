#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "int_sorter.h"

static bool write_int(FILE *fp, int i){
  return fwrite(&i, sizeof(int), 1, fp) == 1;
}

static int read_int(FILE *fp){
  int ret;
  fread(&ret, sizeof(int), 1, fp);
  return ret;
}

int main(){
  char tmpFileName[L_tmpnam+1];
  mkstemp(tmpFileName);

  FILE *fp = fopen(tmpFileName, "wb");
  write_int(fp, 1231);
  write_int(fp, 1);
  write_int(fp, 441);
  fclose(fp);

  int_sorter(tmpFileName, tmpFileName);
  fp = fopen(tmpFileName, "rb");
  int ret = read_int(fp);
  printf("ret is %d\n", ret);
  ret = read_int(fp);
  printf("ret is %d\n", ret);
  ret = read_int(fp);
  printf("ret is %d\n", ret);
  fclose(fp);
  remove(tmpFileName);
  return 0;
}
