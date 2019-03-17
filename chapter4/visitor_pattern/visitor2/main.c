#include <assert.h>
#include <string.h>
#include "validator.h"
#include "validator_view.h"

int main(){
  RangeValidator v1 = newRangeValidator(0, 9);
  PreviousValueValidator v2 = newPreviousValueValidator();
  OddEvenValidator v3 = newOddEvenValidator(true, false);

  char buf[32];
  viewValidator(&v1.base, buf, sizeof(buf));
  // viewValidator内で、viewするためのビジターが作られる
  // v1.accept()はビジターのvisitRangeメンバ関数を使う
  // よってvalidator_viewで定義した動作が行われる
  // 今回のポリモーフィズムの鍵は、各クラスのaccept()がビジターに行って、自分の型のための関数を呼ぶようにしていること
  assert(0 == strcmp(buf, "Range(0-9)"));

  viewValidator(&v2.base, buf, sizeof(buf));
  assert(0 == strcmp(buf, "Previous(0)"));

  viewValidator(&v3.base, buf, sizeof(buf));
  assert(0 == strcmp(buf, "OddEven(Even)"));
}
