INCLUDE_FLAG:= -I../googletest/googletest/include -I../googletest/googletest/src
LINK_FLAG:= -L../googletest/googletest -lgtest -lpthread
COMPILE_FLAG:= -std=c++11 -g -DUNIT_TEST

default:
	g++ $(COMPILE_FLAG) interrupt.c hw.c $(INCLUDE_FLAG) $(LINK_FLAG)

a.out:
	g++ $(COMPILE_FLAG) interrupt.c hw.c $(INCLUDE_FLAG) $(LINK_FLAG)

test: a.out
	./a.out
	rm a.out

