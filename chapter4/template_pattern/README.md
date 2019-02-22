## テンプレートメソッドパターン

リソース(ファイル、メモリなど)は獲得したものを必ず開放しないといけないので管理がやっかい(fopen()->fclose(), malloc()->free())。例えば以下のような、指定されたファイルを読んで１行ごとに数字列を読み、その値の範囲を返すプログラム。

```cpp
int range(const char *pFname){
    FILE *fp = fopen(pFname, "r");
    if (fp == NULL) return -1;
    
    int min = INT_MAX;
    int max = INT_MIN;
    char buf[256];
    
    while(fgets(buf, sizeof(buf), fp) != NULL){
        int val = atoi(buf);
        min = (min > val)? val : min;
        max = (max < val)? val : max;
        }
        
    fclose(fp);
    
    return (max - min);
}
```

しかしもし「ファイルの中に空行が入っていたら-1を返す」という変更を行ったとしよう。ここで単純に

```cpp
while(fgets(buf, sizeof(buf), fp) != NULL){
if(buf[0] == '\n') return -1;
    }
```

としてしまうとfclose()できないのでリソースリークが起きる。こういう場合、breakやgotoを用いて抜けるといった方法も考えられる。C言語でgotoが用いられている場合、多くはリソースの解法が絡んでいる。

#### 前後に定形処理が必要なコード(template1)

リソースを扱うコードが複雑になるのは、リソースの管理コード(獲得と解放)がリソースを使うコードを挟んでいるため。このような場合にはテンプレートメソッドパターンが有効。プログラム中の一部の処理を関数(ポインタ)として差し替えられるようにすることでそれ以外の部分を定形処理として再利用できるようにする。
