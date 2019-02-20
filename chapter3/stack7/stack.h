#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Validator{
  bool (*validate)(struct Validator *pThis, int val);
} Validator;

typedef struct{
  Validator base;
  const int min;
  const int max;
} RangeValidator;

typedef struct{
  Validator base;
  int previousValue;
} PreviousValueValidator;

bool validateRange(Validator *pThis, int val);
bool validaotePrevious(Validator *pThis, int val);

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
  Validator *pValidator;
} Stack;


#endif
