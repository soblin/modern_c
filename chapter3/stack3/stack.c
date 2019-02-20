#include "stack.h"

static bool isStackFull(const Stack *p){
  return (p->top) == (p->size);
}

static bool isStackEmpty(const Stack *p){
  return (p->top) == 0;
}

bool push(Stack *p, int val){
  if(isStackFull(p)) return false;
  p->pBuff[(p->top)++] = val;
  return true;
}

bool pop(Stack *p, int *pRet){
  if(isStackEmpty(p)) return false;
  *pRet = (p->pBuff)[--(p->top)];
  return true;
}

