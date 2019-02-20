#include "stack.h"

int buf[BUF_SIZE];
int top = 0;

static bool isStackFull(void){
  return top == (sizeof(buf) / sizeof(int));
}

static bool isStackEmpty(void){
  return top == 0;
}

bool push(int val){
  if(isStackFull()) return false;
  buf[top++] = val;
  return true;
}

bool pop(int *pRet){
  if(isStackEmpty()) return false;
  *pRet = buf[--top];
  return true;
}
