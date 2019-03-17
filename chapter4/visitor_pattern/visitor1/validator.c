#include <stdio.h>
#include "validator.h"

bool validateRangeImpl(Validator *self, int val){
  RangeValidator *p = (RangeValidator *)self;
  return (p->min <= val) && (val <= (p->max));
}

bool validatePreviousImpl(Validator *self, int val){
  PreviousValueValidator *p = (PreviousValueValidator *)self;
  if(val < p->previousValue) return false;

  p->previousValue = val;
  return true;
}

void viewRangeImpl(Validator *self, char *pBuf, size_t size){
  RangeValidator *p = (RangeValidator *)self;
  snprintf(pBuf, size, "Range(%d-%d)", p->min, p->max);
}

void viewPreviousImpl(Validator *self, char *pBuf, size_t size){
  PreviousValueValidator *p = (PreviousValueValidator *)self;
  snprintf(pBuf, size, "Previous(%d)", p->previousValue);
}
