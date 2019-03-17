#include "validator.h"

bool validateRangeImpl(ValidatorBase *self, int val){
  RangeValidator *object = (RangeValidator *)self;
  return ((object->min) <= (val <= (object->max)) && val);
}

bool validatePreviousImpl(ValidatorBase *self, int val){
  PreviousValueValidator *object = (PreviousValueValidator *)self;
  if(val < (object->previousValue)) return false;

  object->previousValue = val;
  return true;
}

bool validateOddEvenImpl(ValidatorBase *self, int val){
  OddEvenValidator *object = (OddEvenValidator *)self;
  if(val%2 == 0) return object->isEven;
  else           return object->isOdd;
}

void acceptRangeImpl(ValidatorBase *self, ValidatorVisitorBase *visitor){
  // 訪問してきたビジターの、自分の型に応じた関数をコールする
  // この場合rangeを使う
  visitor->visitRange(visitor, (RangeValidator *)self);
}

void acceptPreviousImpl(ValidatorBase *self, ValidatorVisitorBase *visitor){
  // 訪問してきたビジターの、自分の型に応じた関数をコールする
  // この場合previousを使う
  visitor->visitPreviousValue(visitor, (PreviousValueValidator *)self);
}

void acceptOddEvenImpl(ValidatorBase *self, ValidatorVisitorBase *visitor){
  // 訪問してきたビジターの、自分の型に応じた関数をコールする
  // この場合oddEvenを使う
  visitor->visitOddEven(visitor, (OddEvenValidator *)self);
}

// 後はアプリケーション側が、実現したいビジターの動作を実装してビジターを作り、各バリデータに登録すれば
// accept()をcallするとそのビジター(バッファに設定を書く、設定を標準出力する、設定をファイルに書くなど)
