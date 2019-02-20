#include "stack.h"

static bool isStackFull(const Stack *p){
  return (p->top) == (p->size);
}

static bool isStackEmpty(const Stack *p){
  return (p->top) == 0;
}

static bool isRangeOK(const Stack *p, int val){
  // rangeCheckが不要ならOK(そのまま付け加える)
  // あるいは範囲がOKなら
  return (!(p->needRangeCheck)) || ((p->min) <= val && val <= (p->max));
}

bool push(Stack *p, int val){
  if((!isRangeOK(p, val) || isStackFull(p))) return false;
  (p->pBuf)[(p->top)++] = val;
  return true;
}

bool pop(Stack *p, int *pRet){
  if(isStackEmpty(p)) return false;
  *pRet = (p->pBuf)[--(p->top)];
  return true;
}
