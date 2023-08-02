TARGET = main
BINARY = bin

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET) : $(OBJ)
	gcc -lreadline $(OBJ) -o $(TARGET) -lm -g

%.o : %.c
	gcc -lreadline -c $< -o $@ -g

clean :
	rm $(TARGET) *.o
