#include "stack.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  srand((unsigned)time(NULL));
  int buf1[16];
  int buf2[32];
  Stack stack1 = newStack(buf1);
  Stack stack2 = newStack(buf2);
  const int trial = 50;
  int ret = 0;
  for(int i=0; i<trial; ++i){
    if(rand() % 2 == 0){
      push(&stack1, i);
      pop(&stack2, &ret);
    }
    else{
      pop(&stack1, &ret);
      push(&stack2, i);
    }
  }
  return 0;
}
