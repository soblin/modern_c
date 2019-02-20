#include <stdlib.h>
#include <time.h>

#include "stack.h"

int main(){
  srand((unsigned)time(NULL));
  Range range = {10, 40};
  int buf[16];
  Stack stack = newStackWithRangeCheck(buf, &range);
  int ret = 0;
  const int trial = 50;
  for(int i=0; i<trial; ++i){
    if(rand() % 2 == 0) push(&stack, i);
    else pop(&stack, &ret);
  }
  return 0;
}
