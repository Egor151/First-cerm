#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"

int dialog(const char *msgs[], int nmsgs);

int d_load(Table *table);
int d_insert(Table *table);
int d_delete_release(Table *table);
int d_delete(Table *table);
int d_search(Table *table);
int d_print(Table *table);
int d_garbage_collection(Table *table);
int d_save(Table *table);

#endif
