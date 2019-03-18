## C言語とリファクタリング

### Google Test

今回はgit submoduleとしてgoogle-testを利用する。書籍に従い以下のようにしてライブラリを作っておく。

```bash
g++ -std=c++11 -I./include -I. -c ./src/gtest-all.cc -lpthread
```

次に例えば`add01/Makefile`でリンクを行う。

```
INCLUDE_FLAG:= -I../googletest/googletest/include -I../googletest/googletest/src
LINK_FLAG:= -L../googletest/googletest -lgtest -lpthread
COMPILE_FLAG:= -std=c++11 -g

all:
	g++ $(COMPILE_FLAG) add_test.cc add.c $(INCLUDE_FLAG) $(LINK_FLAG)

test: all
	./a.out
```
