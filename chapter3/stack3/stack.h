#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif
  typedef struct {
    int top;
    const size_t size;
    int *pBuff;
  } Stack;

  bool push(Stack *p, int val);
  bool pop(Stack *p, int *pRet);

#define newStack(buf){                          \
    0, sizeof(buf) / sizeof(int), (buf)         \
  }

  //usage:
  // int buf[16];
  // Stack stack = newStack(buf);

#ifdef __cplusplus
}
#endif
#endif
