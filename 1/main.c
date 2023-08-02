#include "inout.h"
#include "process.h"
#include "structs.h"

int main() {
    Matrix mat = new_matr();
    print_matrix(mat);
    for(int i = 0; i < mat.matr_size; i++){
        process(mat.lines_arr[i]);
    }
    print_matrix(mat);
    destroy_matrix(mat);
    return 0;
}
