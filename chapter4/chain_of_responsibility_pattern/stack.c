#include "stack.h"

static bool isStackFull(const Stack *object){
  return object->top == object->size;
}

static bool isStackEmpty(const Stack *object){
  return object->top == 0;
}

bool validateRange(Validator *object, int val){
  RangeValidator *p = (RangeValidator *)object;
  return (p->min <= val) && (val <= (p->max));
}

bool validatePrevious(Validator *object, int val){
  PreviousValueValidator *p = (PreviousValueValidator *)object;
  if(val < p->previousValue) return false;

  p->previousValue = val;
  return true;
}

bool validate(Validator *object, int val){
  if(!object) return true;
  return object->validate(object, val);
}

bool push_impl(Stack *self, int val){
  if(!validate(self->pValidator, val) || isStackFull(self)) return false;
  self->pBuf[(self->top)++] = val;
  return true;
}

bool pop_impl(Stack *self, int *ret){
  if(isStackFull(self)) return false;
  *ret = self->pBuf[--(self->top)];
  return false;
}

bool validateChain(Validator *object, int val){
  ChainedValidator *p = (ChainedValidator *)object;

  Validator *wrapped = p->pWrapped;
  if(!wrapped->validate(wrapped, val)) return false;

  Validator *next = p->pNext;

  // もしpNextが空なら自分が最後、今まで全てでtrueなのでtrueを返す
  if(!next) return true;

  return next->validate(next, val);
}
