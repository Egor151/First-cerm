#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

int get_int(int *res, int min, int max, char *msg);
int fget_int(FILE *fd, int *res, int min, int max);
char *readline(char *msg);
char *freadline(FILE *fd);

#endif // INPUT_H
