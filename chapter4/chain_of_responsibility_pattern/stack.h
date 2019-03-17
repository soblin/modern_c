#ifndef STACK_H_
#define STACK_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct Validator{
  bool (*const validate)(struct Validator *self, int val);
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

typedef struct{
  Validator base;
  Validator *pWrapped;
  Validator *pNext;
} ChainedValidator;

typedef struct Stack{
  // メンバ変数
  int top;
  const size_t size;
  int *pBuf;
  Validator *pValidator;
  
  // メンバ関数
  bool (*push)(struct Stack *self, int val);
  bool (*pop)(struct Stack *self, int *ret);  
} Stack;

bool push_impl(Stack *self, int val);
bool pop_impl(Stack *self, int *ret);

bool validateRange(Validator *object, int val);
bool validatePrevious(Validator *object, int val);
bool validateChain(Validator *object, int val);

// コンストラクタ
#define newRangeValidator(min, max)             \
  {{validateRange}, (min), (max)}

#define newPreviousValueValidator()             \
  {{validatePrevious}, 0}

#define newChainedValidator(wrapped, next)      \
  {{validateChain}, (wrapped), (next)}

#define newStack(buf){                          \
    0, sizeof(buf) / sizeof(int), (buf),        \
        NULL, push_impl, pop_impl               \
        }

#define newStackWithValidator(buf, pValidator){ \
    0, sizeof(buf) / sizeof(int), (buf),        \
        pValidator, push_impl, pop_impl         \
        }

#endif
