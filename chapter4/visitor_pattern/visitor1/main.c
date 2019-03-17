#include <assert.h>
#include <string.h>
#include "validator.h"

int main(){
  RangeValidator v1 = newRangeValidator(0, 9);
  char buf[32];
  v1.base.view(&v1.base, buf, sizeof(buf));

  assert(0 == strcmp("Range(0-9)", buf));

  PreviousValueValidator v2 = newPreviousValueValidator();
  v2.base.view(&v2.base, buf, sizeof(buf));
  assert(0 == strcmp("Previous(0)", buf));
}
