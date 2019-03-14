#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "array_list.h"

// データを末尾に追加し、自分自身を返す
// サイズが足りない場合はassertエラーになる
ArrayList *add_to_array_list(ArrayList *self, void *pData){
  assert(self->capacity > self->index);
  self->array[self->index++] = pData;
  return self;
}

// 指定されたデータを削除し、削除されたデータを返す
// 見つからない場合はNULLが返る
void *remove_from_array_list(ArrayList *self, void *pData){
  for(int i=0; i<self->index; ++i){
    if(self->array[i] == pData){
      memmove(self->array+i, self->array+i+1, (self->index-i-1) * sizeof(void*));
      --(self->index);
      return pData;
    }
  }

  return NULL;
}

// 指定された場所のデータを返す
// indexの値がデータの格納されている範囲外の場合はassertエラーになる
void *get_from_array_list(ArrayList *self, int index){
  assert(0 <= index && index < (self->index));
  return self->array[index];
}

size_t array_list_size(ArrayList *self){
  return self->index;
}
