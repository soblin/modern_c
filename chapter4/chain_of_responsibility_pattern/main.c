#include <assert.h>
#include "stack.h"

int main(){
  RangeValidator rangeValidator = newRangeValidator(0, 9);
  PreviousValueValidator previousValidator = newPreviousValueValidator();

  ChainedValidator prevChain = newChainedValidator(&previousValidator.base, NULL);
  ChainedValidator rangeChain = newChainedValidator(&rangeValidator.base, &prevChain.base);

  int buf[16];
  Stack stack = newStackWithValidator(buf, &rangeChain.base);
  bool ret = true;
  ret = stack.push(&stack, -1);
  assert(ret == false);
  ret = stack.push(&stack, 5);
  assert(ret == true);
  ret = stack.push(&stack, 4);
  assert(ret == false);
  ret = stack.push(&stack, 9);
  assert(ret == true);
  ret = stack.push(&stack, 10);
  assert(ret == false);
}
