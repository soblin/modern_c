CC := gcc
CFLAGS := -Wall -g

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

main: main.o stack.o
	$(CC) $(CFLAGS) -o main main.o stack.o

clean:
	rm *.o main

