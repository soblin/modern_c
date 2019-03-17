#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct Validator{
  bool (*const validate)(struct Validator *self, int val);
  void (*const view)(struct Validator *self, char *pBuf, size_t size);
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

void viewRangeImpl(Validator *self, char *pBuf, size_t size);
void viewPreviousImpl(Validator *self, char *pBuf, size_t size);

bool validateRangeImpl(Validator *self, int val);
bool validatePreviousImpl(Validator *self, int val);

#define newRangeValidator(min, max)             \
  {{validateRangeImpl, viewRangeImpl}, (min), (max)}

#define newPreviousValueValidator()             \
  {{validatePreviousImpl, viewPreviousImpl}, 0}

#endif
