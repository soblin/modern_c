#include "add.h"

static int add(int, int);

int cal(int i1, int i2){
  return add(i1, i2);
}

static int add(int i1, int i2){
  return i1 + i2;
}
