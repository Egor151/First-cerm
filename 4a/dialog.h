#ifndef DIALOG_H
#define DIALOG_H

#include "tree.h"

int dialog(const char *msgs[], int nmsgs);

int d_create(Tree *tree);
int d_insert(Tree *tree);
int d_delete(Tree *tree);
int d_search(Tree *tree);
int d_special(Tree *tree);
int d_walk(Tree *tree);
int d_print(Tree *tree);
int d_destroy(Tree *tree);

#endif // DIALOG_H
