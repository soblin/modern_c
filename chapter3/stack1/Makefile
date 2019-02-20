CC := gcc
FLAGS := -Wall -Wextra -g

main.o: main.c
	$(CC) $(FLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

main: stack.o main.o stack.h
	$(CC) $(FLAGS) -o main main.o stack.o

clean:
	rm *.o main
