#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Line{
    int line_size; 
    int *line_arr; 
} Line;

typedef struct Matrix{
    int matr_size;
    Line *lines_arr;
} Matrix;

#endif
