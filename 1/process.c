#include <stdlib.h>
#include <stdio.h>
#include "structs.h"


int max(Line line){
    int max_v = -10000000;
    for(int i = 0; i < line.line_size; i++){
        if(line.line_arr[i] > max_v) max_v = line.line_arr[i];
    }
    return max_v;
}

int min(Line line){
    int min_v = 10000000;
    for(int i = 0; i < line.line_size; i++){
        if(line.line_arr[i] < min_v) min_v = line.line_arr[i];
    }
    return min_v;
}

void process(Line line){
    int max_elem = max(line), min_elem = min(line);
    int *arr = line.line_arr;
    int *max_ind = NULL, max_len = 0, *min_ind = NULL, min_len = 0;
    for(int i = 0; i < line.line_size; i++){
        if(arr[i] == max_elem){
            max_len++;
            max_ind = realloc(max_ind, max_len * sizeof(int));
            max_ind[max_len - 1] = i;
        }
        if(arr[i] == min_elem){
            min_len++;
            min_ind = realloc(min_ind, min_len * sizeof(int));
            min_ind[min_len - 1] = i;
        }
    }
    if(max_len > min_len){
        for(int i = 0; i < min_len; i++){
            int tmp = arr[min_ind[i]];
            arr[min_ind[i]] = arr[max_ind[i]];
            arr[max_ind[i]] = tmp;
        }
    } else{
        for(int i = 0; i < max_len; i++){
            int tmp = arr[min_ind[i]];
            arr[min_ind[i]] = arr[max_ind[i]];
            arr[max_ind[i]] = tmp;
        }
    }
    free(max_ind); free(min_ind);
    line.line_arr = arr;
}
