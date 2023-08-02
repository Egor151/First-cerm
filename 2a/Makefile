CC = /usr/bin/clang
CFLAGS = -g -Wall -Wextra
TARGET = main.c mymath.c queue.c computation.c
OBJ = main.o mymath.o queue.o computation.o

list:
	$(CC) -c $(CFLAGS) $(TARGET)
	$(CC) $(OBJ) -o lab2

vector:
	$(CC) -DVECTOR -c $(CFLAGS) $(TARGET)
	$(CC) $(OBJ) -o lab2

clean:
	rm -rf lab2
	rm -rf *.o
