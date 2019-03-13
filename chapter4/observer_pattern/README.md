## オブザーバーパターン

前節のコードで存在しないファイルを指定するとエラーメッセージが２回表示される。それは次のようにして`file_error`が２回呼ばれるためである。

```cpp
static bool reader(FileContext *p){
    MyFileContext *pFileCtx = (MyFilecontext *)p;
    MyBufferContext *pBufCtx = pFileCtx->pBufCtx;
    long size = file_size(p); // ここで-1が返ってくる
    if(size == -1){
        file_error(pBufCtx->pAppCtx);
        return false;
    }
}
```

ここで１回目のエラーが表示される。次にfalseが返った後`do_with_buffer`内において再度

```cpp
static bool do_with_buffer(BufferContext *p){
    MyBufferContext *pBufCtx = (MyBufferContext *)p;
    MyFileContext readFileCtx = 
        {{NULL, pBufCtx->pAppCtx->pFname, "rb", reader}, pBufCtx};
    if(!access_file(&readFileCtx.base)){
        file_error(pBufCtx->pAppCtx);
        return false;
        }
}
```

のようにして`file_error`が呼ばれるため２回目のエラーが表示されてしまう。どうも後者のコードは余分なように見える。

そもそも`access_file`から呼び出されるユーザー関数はファイルアクセス以外の処理もするはずで、`access_file`がfalseを返したからといって一律にそれをファイルエラーとして判定するのは乱暴。かといって`access_file`では`fclose()`が呼ばれるのでここでのエラーを無視するわけにもいかない。

`access_file`関数内の`fclose()`呼び出し部分から`file_error`を呼びだせばよいのだろうか？しかし`access_file`は共通関数であり`file_error`はアプリケーション関数であるから、`file_error`の呼び出しを`access_file`内に埋め込むこともできない。つまり`fclose()`がエラーを起こすことは知りたいけれどエラー処理のコードを直接その場所に書くことはできないというジレンマを抱えている。このようにある場所での処理の状況を別の場所から管理したいけれど監視する側と監視される側をお互いに依存させたくない。このような場合にオブザーバーパターンを活用できる。

今回のファイル処理においては

```cpp
bool access_file(FileAccessorContext *pThis){
    assert(pThis);
    bool ret = pThis->processor(pThis);
    if(pThis->fp != NULL){
        if(fclose(pThis->fp) != 0) ret = false; // !!!Candidate1!!!
    }
    return ret;
}

FILE *get_file_pointer(FileAccessorContext *pThis){
    assert(pThis);
    if(pThis->fp == NULL)
        pThis->fp = fopen(pThis->pFname, pThis->pMode); // !!!Candidate2!!!
        
    return pThis->fp;
}
```

これらの関数の中でエラーが起きる可能性があるのはCandidate1,2 であるから、これらのエラーを外部に通知できるようにする。まず`FileAccessorContext`にオブザーバーオブジェクトを登録できるようにする。
