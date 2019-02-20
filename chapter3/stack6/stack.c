#include "stack.h"

// Validatorのvalidateと同じシグネチャにする
bool validateRange(Validator *pThis, int val){
  // validatorがNULLならチェックしない
  if(!pThis) return true;
  
  const Range *pRange = (Range *)(pThis->pData);
  // min以上max以下ならtrueを返す
  return ( (pRange->min) <= val ) && ( val <= (pRange->max) );
}

bool validatePrevious(Validator *pThis, int val){
  // validatorがNULLならチェックしない
  if(!pThis) return true;
  
  PreviousValue *pPreviousValue = (PreviousValue *)(pThis->pData);
  // valがpreviousValue以下ならfalseを返す
  if(val <= (pPreviousValue->previousValue)) return false;
  // もしvalがpreviousValueより大きければtrueを返してpreviousValueを上書き
  pPreviousValue->previousValue = val;
  return true;
}

static bool isStackFull(const Stack *stack){
  return (stack->top) == (stack->size);
}

static bool isStackEmpty(const Stack *stack){
  return (stack->top) == 0;
}

bool push(Stack *stack, int val){
  Validator *pValidator = stack->validator;
  if(isStackFull(stack) || !(pValidator->validate(pValidator, val)))
    // pushしない
    return false;

  (stack->pBuf)[(stack->top)++] = val;
  return true;
}

bool pop(Stack *stack, int *pRet){
  if(isStackEmpty(stack)) return false;
  *pRet = (stack->pBuf)[--(stack->top)];
  return true;
}

