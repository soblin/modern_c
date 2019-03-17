## チェインオブレスポンシビリティパターン

前章では範囲チェックバリデータに対して継承によって偶数奇数チェックを行うチェック機能をスタックに追加した。しかし偶数奇数チェックだけでなく他のバリデータも追加したくなるかもしれない。

仮に２種類のバリデータAとBがあったら、これらを単独に使用するケース以外にA->B、B->Aの２ケースも考えられるので、これらを継承で解決しようとすると合計で４つのクラスが必要になる。バリデータの数が増えるとこの組み合わせの個数は爆発的に増えてしまう。

この問題には`Chain of Responsibility`パターンを利用することで対処できる。このパターンではオブジェクトを数珠つなぎにしておいて、一方の端に処理を依頼する。処理を依頼されたオブジェクトは自分に処理が可能な処理であれば自分で処理して結果を返すが、もし自分には処理できないと判断したら次のオブジェクトに処理を依頼する。このようにしてオブジェクトをチェインしていく。

```cpp
typedef struct ChaindValidator{
    Validator base;
    Validator *pWapped;
    Validator *pNext;
} ChainedValidator
```

`ChainedValidator`はそれ自身検証機能を持たず、`pWrapped`と`pNext`を用いて検証を行う。

```cpp
bool ValidateChain(Validator *p, int val){
    ChainedValidator *pThis = (ChainedValidator *)p;
    
    p = pThis->pWrapped;
    if(!p->validate(p, val)) return false;
    
    p = pThis->pNext;
    if(p == NULL) return true;
    return p->validate(p, val);
}
```

処理の流れは

1. まず`pWrapped`で指されれているバリデータを用いて検証し、falseが返ればそのままfalseを返す(検証失敗)。
2. もしtrueを返したら、次に`pNext`を調べる。
3. もし`pNext`がNULLだったら、今までのバリデータが全てtrueを返したことになる。よってtrueを最後に返す。
4. もし`pNext`がNULLでなければ`pNext`に処理を委ねる。

実装の注意点としては、このチェインにループが含まれてはいけないことである。
