#include <stdio.h>
#include "validator_view.h"

static void rangeView(ValidatorVisitorBase *object, RangeValidator *validator);
static void previousValueView(ValidatorVisitorBase *object, PreviousValueValidator *validator);
static void oddEvenView(ValidatorVisitorBase *object, OddEvenValidator *validator);

typedef struct{
  ValidatorVisitorBase base;
  char *pBuf;
  size_t size;
} ViewVisitor;

void viewValidator(ValidatorBase *object, char *pBuf, size_t size){
  ViewVisitor visitor = {{rangeView, previousValueView, oddEvenView}, pBuf, size};
  // もしこの型がrangeだったら、このaccept()関数はacceptRange()になっているはず。
  // そのためacceptRange()はvisitorのrangeViewを呼びに行くはず。
  object->accept(object, &visitor.base);
}

// ビジターが各クラスに対して行う動作
static void rangeView(ValidatorVisitorBase *object, RangeValidator *validator){
  ViewVisitor *visitor = (ViewVisitor *)object;
  snprintf(visitor->pBuf, visitor->size, "Range(%d-%d)", validator->min, validator->max);
}

static void previousValueView(ValidatorVisitorBase *object, PreviousValueValidator *validator){
  ViewVisitor *visitor = (ViewVisitor *)object;
  snprintf(visitor->pBuf, visitor->size, "Previous(%d)", validator->previousValue);
}

static void oddEvenView(ValidatorVisitorBase *object, OddEvenValidator *validator){
  ViewVisitor *visitor = (ViewVisitor *)object;
  snprintf(visitor->pBuf, visitor->size, "OddEven(%s)", (validator->isEven)? "Even" : "Odd");
}
