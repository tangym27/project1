all: main.o shell.o
	gcc -o ./a.out main.o shell.o

shell.o: shell.h main.c
		gcc -c -g shell.c

main.o: main.c shell.h
	gcc -c -g main.c

run:
	./a.out
clean:
	rm *.out
	rm *.o
	rm *.txt
