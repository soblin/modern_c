#include "stack.h"
#include <stdlib.h>
#include <time.h>

int main(){
  RangeValidator validator1 = newRangeValidator(10, 40);
  PreviousValueValidator validator2 = newPreviousValueValidator();
  int buf1[16];
  int buf2[32];
  Stack stack1 = newStackWithValidator(buf1, &validator1.base);
  Stack stack2 = newStackWithValidator(buf2, &validator2.base);

  const int trial = 200;
  int ret = 0;
  srand((unsigned)time(NULL));
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
