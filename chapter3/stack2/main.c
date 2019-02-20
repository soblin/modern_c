#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
  srand((unsigned)time(NULL));
  const int trial = 50;
  for(int i=0; i<trial; ++i){
    if(rand() % 2 == 0){
      push(i);
    }
    else{
      int ret;
      pop(&ret);
    }
  }
  return 0;
}
