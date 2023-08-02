#include <stdlib.h>
#include "mymath.h"

double my_sin(int deg, int n) {
    if (n <= 0){
        return 0.0;
    }

    double arg_r = M_PIl * (double)deg / 180.0;
    double part = arg_r; 
    double res = arg_r;

    for (int i = 2; i < n; ++i) {
        part *= (-1.0) * arg_r * arg_r / ((2 * i - 2) * (2 * i - 1));
        res += part;
    }

    return res;
}

int get_rand(int min, int max) {
    return min + rand() % (max + 1 - min);
}


