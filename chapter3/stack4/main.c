#include "stack.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  srand((unsigned)time(NULL));
  int buf[16];
  Stack stack = newStackWithRangeChecker(buf, 10, 40);
  int ret = 0;
  const int trial = 50;
  for(int i=0; i<trial; ++i){
    if(rand() % 2 == 0) push(&stack, i);
    else pop(&stack, &ret);
  }
  return 0;
}
