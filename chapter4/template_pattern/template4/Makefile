OBJS := main.o file_accessor.o buffer.o int_sorter.o

all: ${OBJS}
	gcc -g -o a.out $(OBJS)

main.o: main.c
	gcc -c -g main.c

file_accessor.o: file_accessor.c
	gcc -c -g file_accessor.c

buffer.o: buffer.c
	gcc -c -g buffer.c

int_sorter.o: int_sorter.c
	gcc -c -g int_sorter.c

.PHONY: clean
clean:
	rm *.o a.out
