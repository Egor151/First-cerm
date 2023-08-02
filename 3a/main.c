#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "dialog.h"

int (*fptr[])(Table *) = {NULL, d_insert, d_find, d_delete, d_print, d_garbage_collection};
const char *msgs[] = {"0. Exit", "1. Insert", "2. Find", "3. Delete", "4. Print", "5. Garbage collection"};
int opts_size = 6;

int main() {
    Table *table = calloc(1, sizeof(Table));
    if (!table) {
        return 1;
    }

    int msize = 0, status = get_int(&msize, "Enter table max size: --> ");
    if (msize <= 0 || !status) {
        free(table);
        return 1;
    }
    table->msize = msize;

    int rc = 0;
    while ((rc = dialog(msgs, opts_size))) {
        if (!fptr[rc](table)) {
            break;
        }
    }

    for (int i = 0; i < table->csize; i++) {
        free_element(table->ks + i);
    }
    free(table->ks);
    free(table);

    return 0;
}
