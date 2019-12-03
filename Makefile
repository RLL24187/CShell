all: shell.o main.o
	gcc -o shell.out shell.o main.o

shell.o: shell.c shell.h
	gcc -c shell.c

main.o: main.c shell.h
	gcc -c main.c

clean:
	rm -f *.o *.out shell
run:
	./shell.out
