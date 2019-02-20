#include "stack.h"

static bool isStackFull(const Stack *p){
  return (p->top) == (p->size);
}

static bool isStackEmpty(const Stack *p){
  return (p->top) == 0;
}

static bool isRangeOK(const Range *p, int val){
  // (p->pRange)がNULLならOK
  // もちろんvalが(p)の範囲内ならOK
  bool cond1 = (p == NULL);
  bool cond2 = (p->min <= val && val <= p->max);
  return cond1 || cond2;
}

bool push(Stack *p, int val){
  if(!isRangeOK(p->pRange, val) || isStackFull(p)) return false;
  (p->pBuf)[p->top++] = val;
  return true;
}

bool pop(Stack *p, int *pRet){
  if(isStackEmpty(p)) return false;
  *pRet = (p->pBuf)[--(p->top)];
  return true;
}

