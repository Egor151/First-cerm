all: lib
	gcc -c dialog.c -o dialog.o 
	gcc -c main.c -o main.o

	gcc -o bin main.o dialog.o -L. -ltable

lib:
	gcc -c table.c -o table.o
	ar rcs libtable.a table.o

clean:
	rm -rf bin *.o *.a
