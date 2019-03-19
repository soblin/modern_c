INCLUDE_FLAG:= -I../googletest/googletest/include -I../googletest/googletest/src
LINK_FLAG:= -L../googletest/googletest -lgtest -lpthread
COMPILE_FLAG:= -std=c++11 -DUNIT_TEST -g

default:
	g++ $(COMPILE_FLAG) interrupt_test.cc  $(INCLUDE_FLAG) $(LINK_FLAG)

a.out:
	g++ $(COMPILE_FLAG) interrupt_test.cc $(INCLUDE_FLAG) $(LINK_FLAG)

test: a.out
	./a.out
	rm a.out

