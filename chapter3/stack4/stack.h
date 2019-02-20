#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int top;
  const size_t size;
  int *pBuf;

  const bool needRangeCheck;
  const int min;
  const int max;
} Stack;

#define newStack(buf){                                  \
    0, sizeof(buf) / sizeof(int), (buf), false, 0, 0    \
}

#define newStackWithRangeChecker(buf, min, max){        \
    0, sizeof(buf) / sizeof(int), (buf), true, min, max \
}

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#endif
