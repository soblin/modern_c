#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct{
  const int min;
  const int max;
} Range;

typedef struct{
  int top;
  const size_t size;
  int *pBuf;
  Range *pRange;
} Stack;

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#define newStack(buf){                          \
    0, sizeof(buf) / sizeof(int), (buf), NULL   \
}

#define newStackWithRangeCheck(buf, pRange){    \
    0, sizeof(buf) / sizeof(int), (buf), pRange \
}

#endif
