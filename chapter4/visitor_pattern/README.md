## ビジターパターン

バリデータの設定を表示できるようにしたいとする。例えば`RangeValidator`ならば`"Range(0-9)"`のように。一番簡単なのはバリデータ自身にこういった表示用の関数を追加することである。

```cpp
typedef struct Validator{
    bool (*const validate)(struct Validator *self, void *validate_data);
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
} PreviousValidator;

void viewRangeImpl(Validator *self, char *pBuf, size_t size);
void viewPreviousImpl(Validator *self, char *pBuf, size_t size);
```

しかしこのような表示関数は本当にバリデータ自身が提供すべきだろうか？今回のようにひとつだけなら問題ないがこれから

- バリデータの設定をファイルに保存する関数が必要になる
- バリデータのチェインの中に同じバリデータが繰り返し出てくるような間違った構成を顕正するような機能が必要になる

といった可能せもある。

こうした少しでもバリデータに関係する機能をバリデータ自身に追加してしまうと、バリデータ本来の機能が薄れてしまう。このように何でもかんでもオブジェクトに詰め込んでしまうと独立性が失われ、オブジェクト指向のメリットが失われてしまう。

ここで以下のようにするとバリデータの表示結果を得たいとする。

```cpp
void printfValidator(Validator *p, char *pBuf, size_t size);
```

この関数は受け取るバリデータに対してそのバリデータの型の固有の動作をさせなければならない(ポリモーフィズム)。ポインタではそれを判別できないので、ナイーブな解決策の一つとしてはバリデータにtype idを持たせることが考えられる。

```cpp
typedef enum{
    Range = 0,
    Previous
} ValidatorType;

typedef struct Validator{
    const int type_id;
    bool (*const validate)(struct Validator *self, int val);
    void (*const view)(struct Validator *self, char *pBuf, size_t size);
} Validator;

void printValidator(Validator *object, char *pBuf, size_t size){
    switch(object->type_id){
        case Range:
            p = (RangeValidator *)object;
            p->view(object, pBuf, size);
            break;
        case Previous:
            p = (PreviousValueValidator *)object;
            p->view(object, pBuf, size);
            break;
        default:
            break;
    }
}
```

しかしこうしたid管理は煩雑で、プログラムの拡張に伴って破綻しやすく、基本的には避けるべきである。そもそも外からオブジェクトの種類を調べて、それに応じて条件分岐をするのはオブジェクト指向のやり方に反している。

### オブジェクトにtype idを持たせたくなったら黄色信号

オブジェクト指向ではポリモーフィズムにより、型に応じた条件分岐を削除する。ビジターパターンもこの方針に従う。

