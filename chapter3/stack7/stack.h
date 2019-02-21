#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

// Validatorのインターフェース
typedef struct Validator{
  bool (*validate)(struct Validator *pThis, int val);
} Validator;

// Validatorのスーパークラス
typedef struct{
  Validator base;
  const int min;
  const int max;
} RangeValidator;

typedef struct{
  Validator base;
  int previousValue;
} PreviousValueValidator;

// この２つも、実際はそれぞれ RangeValidatorやPreviousValueValidator
// を使うことは自明だが、インターフェースとしてはValidatorへのポインタを取るようにする
bool validateRange(Validator *pThis, int val);
bool validatePrevious(Validator *pThis, int val);

#define newRangeValidator(min, max){            \
    {validateRange}, min, max                   \
}

#define newPreviousValueValidator(){            \
    {validatePrevious}, 0                       \
}

typedef struct{
  int top;
  const size_t size;
  int *pBuf;
  // インターフェースへのポインタをもたせる
  Validator *pValidator;
} Stack;

#define newStack(buf){                          \
    0, sizeof(buf) / sizeof(int), (buf), NULL   \
}

#define newStackWithValidator(buf, pValidator){     \
    0, sizeof(buf) / sizeof(int), (buf), pValidator \
}

bool push(Stack *stack, int val);
bool pop(Stack *stack, int *pRet);

#endif
