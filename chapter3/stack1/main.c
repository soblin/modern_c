#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int arcg, char **argv){
  srand((unsigned)time(NULL));
  int ret = 0;
  bool success = true;
  for(int i=0; i<buf_size; ++i){
    if(rand() % 2 == 0){
      success = push(i);
    }
    else{
      success = pop(&ret);
    }
  }
  return 0;
}
