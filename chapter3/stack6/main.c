#include <stdlib.h>
#include <time.h>

#include "stack.h"

int main(){
  Range range = {10, 40};
  Validator validator1 = rangeValidator(&range);
  int buf1[32];
  Stack stack1 = newStackWithValidator(buf1, &validator1);

  PreviousValue previous = {0};
  Validator validator2 = previousValidator(&previous);
  int buf2[24];
  Stack stack2 = newStackWithValidator(buf2, &validator2);
  
  srand((unsigned)time(NULL));
  int ret = 0;
  const int trial = 100;
  for(int i=0; i<trial; ++i){
    if(rand() % 2 == 0){
      push(&stack1, i);
      pop(&stack2, &ret);
    }
    else{
      push(&stack2, i);
      pop(&stack1, &ret);
    }
  }
  return 0;
}
