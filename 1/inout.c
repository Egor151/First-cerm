#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


void check(int *num){
    char c[80];
    while(scanf("%d", num) != -1){
        printf("Error. Enter value: \n");
        scanf("%*c", c);
    }
}

Matrix new_matr(){

    printf("Enter matr_size: \n");
    int m_size = 0;
    check(&m_size);

    Matrix matr = {m_size, NULL}; 

    matr.lines_arr = calloc(matr.matr_size, sizeof(Line)); 
    for(int i = 0; i < matr.matr_size; i++){
        printf("Enter line_size\n");
        check(&matr.lines_arr[i].line_size);
        matr.lines_arr[i].line_arr = calloc(matr.lines_arr[i].line_size, sizeof(int)); 
        for(int j = 0; j < matr.lines_arr[i].line_size; j++){
            printf("Enter elem\n");
            int elem = 0;
            check(&elem);
            matr.lines_arr[i].line_arr[j] = elem;
        }
    }

    return matr;
}

void print_matrix(Matrix mat) {
    for(int i = 0; i < mat.matr_size; i++){
        for(int j = 0; j < mat.lines_arr[i].line_size; j++){
            printf("%d ", mat.lines_arr[i].line_arr[j]);
        }
        printf("\n");
    }
}

void destroy_matrix(Matrix mat) {
    for(int i = 0; i <mat.matr_size; i++){
        free(mat.lines_arr[i].line_arr);
    }
    free(mat.lines_arr);
}
