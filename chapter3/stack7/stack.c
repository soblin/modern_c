#include "stack.h"

// ここでアップキャストが行われるのがポイント
bool validateRange(Validator *pThis, int val){
  RangeValidator *validator = (RangeValidator *)(pThis);
  return (validator->min) <= val && val <= (validator->max);
}

// ここでアップキャストが行われるのがポイント
bool validatePrevious(Validator *pThis, int val){
  PreviousValueValidator *validator = (PreviousValueValidator *)(pThis);
  if(val <= (validator->previousValue)) return false;
  validator->previousValue = val;
  return true;
}

static bool isStackFull(const Stack *stack){
  return (stack->top) == (stack->size);
}

static bool isStackEmpty(const Stack *stack){
  return (stack->top) == 0;
}

static bool validate(Validator *p, int val){
  if(!p) return true;
  return p->validate(p, val);
}

bool push(Stack *stack, int val){
  if(isStackFull(stack) || !validate(stack->pValidator, val))
    return false;
  (stack->pBuf)[(stack->top)++] = val;
  return true;
}

bool pop(Stack *stack, int *pRet){
  if(isStackEmpty(stack)) return false;
  *pRet = (stack->pBuf)[--(stack->top)];
  return true;
}
