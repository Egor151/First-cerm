#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"

int dialog(const char *msgs[], int nmsgs);

int d_create(Table *table);
int d_insert(Table *table);
int d_delete(Table *table);
int d_search(Table *table);
int d_print(Table *table);
int d_destroy(Table *table);

#endif // DIALOG_H
