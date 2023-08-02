#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"

#define BUFFER_SIZE 80

int get_int(int *res, char *msg);
int dialog(const char *msgs[], int N);

int d_insert(Table *table);
int d_delete(Table *table);
int d_print(Table *table);
int d_find(Table *table);
int d_garbage_collection(Table *table);

#endif // DIALOG_H
