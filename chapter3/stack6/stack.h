#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif
  
  typedef struct Validator{
    // thisポインタを明示的に与えないといけないのが欠点
    bool (*validate)(struct Validator *pThis, int val);
    // 範囲チェックしたいときはここにRangeのポインタを、
    // 前回より大きいかチェックしたいときはPreviousValueへのポインタを入れる
    void *pData;
  } Validator;

  typedef struct{
    const int min;
    const int max;
  } Range;

  typedef struct{
    int previousValue;
  } PreviousValue;

  bool validateRange(Validator *pThis, int val);
  bool validatePrevious(Validator *pThis, int val);

#define rangeValidator(pRange){                 \
    validateRange, pRange                       \
        }

#define previousValidator(pPrevious){           \
    validatePrevious, pPrevious                 \
        }

  typedef struct{
    int top;
    const size_t size;
    int *pBuf;
    Validator *validator;
  } Stack;

  bool push(Stack *stack, int val);
  bool pop(Stack *stack, int *pRet);
  
#define newStack(buf){                          \
    0, sizeof(buf) / sizeof(int), (buf), NULL   \
        }

#define newStackWithValidator(buf, pValidator){         \
    0, sizeof(buf) / sizeof(int), (buf), (pValidator)   \
        }

#ifdef __cplusplus
}
#endif

#endif
