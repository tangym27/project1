all: main.o shell.o
	gcc main.o shell.o

main.o: main.c
	gcc -c -g main.c

shell.o: shell.c shell.h
	gcc -c -g shell.c

run:
	./a.out

clean:
	rm -rf *.o a.out
