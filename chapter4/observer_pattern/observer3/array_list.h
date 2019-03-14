#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct ArrayList{
  const int capacity;
  // void**にするよりはObserverBaseへのポインタの配列にするほうが良いのでは
  void **array;
  size_t index;

  struct ArrayList *(*const add)(struct ArrayList *self, void *pData);
  void *(*const remove)(struct ArrayList *self, void *pData);
  void *(*const get)(struct ArrayList *self, int index);
  size_t (*const size)(struct ArrayList *self);
} ArrayList;

ArrayList *add_to_array_list(ArrayList *self, void *pData);
void *remove_from_array_list(ArrayList *self, void *pData);
void *get_from_array_list(ArrayList *self, int index);
size_t array_list_size(ArrayList *self);

#define new_array_list(array){sizeof(array) / sizeof(void*), array, 0, add_to_array_list, remove_from_array_list, get_from_array_list, array_list_size}

#endif
