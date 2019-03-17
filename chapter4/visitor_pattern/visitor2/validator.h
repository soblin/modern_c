#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <stddef.h>
#include <stdbool.h>

struct ValidatorVisitorBase;

typedef struct ValidatorBase{
  bool (*const validate)(struct ValidatorBase *self, int val);
  void (*const accept)(struct ValidatorBase *self, struct ValidatorVisitorBase *visitor);
} ValidatorBase;

typedef struct{
  ValidatorBase base;
  const int min;
  const int max;
} RangeValidator;

typedef struct{
  ValidatorBase base;
  int previousValue;
} PreviousValueValidator;

typedef struct{
  ValidatorBase base;
  const bool isEven;
  const bool isOdd;
} OddEvenValidator;

typedef struct ValidatorVisitorBase{
  void (*const visitRange)(struct ValidatorVisitorBase *self, RangeValidator *p);
  void (*const visitPreviousValue)(struct ValidatorVisitorBase *self, PreviousValueValidator *p);
  void (*const visitOddEven)(struct ValidatorVisitorBase *self, OddEvenValidator *p);
} ValidatorVisitorBase;

// ビジターのvisitRangeをcallする
void acceptRangeImpl(ValidatorBase *self, ValidatorVisitorBase *visistor);
// ビジターのvisitPreviousをcallする
void acceptPreviousImpl(ValidatorBase *self, ValidatorVisitorBase *visitor);
// ビジターのvisitOddEvenをcallする
void acceptOddEvenImpl(ValidatorBase *self, ValidatorVisitorBase *visitor);

bool validateRangeImpl(ValidatorBase *self, int val);
bool validatePreviousImpl(ValidatorBase *self, int val);
bool validateOddEvenImpl(ValidatorBase *self, int val);

#define newRangeValidator(min, max)             \
  {{validateRangeImpl, acceptRangeImpl}, (min), (max)}

#define newPreviousValueValidator()             \
  {{validatePreviousImpl, acceptPreviousImpl}, 0}

#define newOddEvenValidator(even, odd)          \
  {{validateOddEvenImpl, acceptOddEvenImpl}, (even), (odd)}

#endif
