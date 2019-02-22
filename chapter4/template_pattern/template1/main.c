#include "range.h"
#include <stdio.h>

int main(){
  const char filename[] = "toydata.txt";
  int result = range(filename);
  printf("result is %d\n", result);
  return 0;
}
