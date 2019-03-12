#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "int_sorter.h"

static bool write_int(FILE *fp, int i) {
    return fwrite(&i, sizeof(int), 1, fp) == 1;
}

static int read_int(FILE *fp) {
    int ret;
    fread(&ret, sizeof(int), 1, fp);
    return ret;
}

int main(){
  const char input[] = "input.bin";
  const char output[] = "output.bin";

  FILE *fp = fopen(input, "wb");
  bool result = write_int(fp, 1231);
  result = write_int(fp, 1);
  result = write_int(fp, 441);
  fclose(fp);

  int_sorter(input, output);

  fp = fopen(output, "rb");
  int val = read_int(fp);
  assert(val == 1);
  val = read_int(fp);
  assert(val == 441);
  val = read_int(fp);
  assert(val == 1231);

  fclose(fp);
  return 0;
}
