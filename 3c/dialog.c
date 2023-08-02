#include "dialog.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int dialog(const char *msgs[], int nmsgs)
{
    for (int i = 0; i < nmsgs; i++) {
        printf("%d. %s\n", i, msgs[i]);
    }

    int msg;
    if (get_int(&msg, 0, nmsgs - 1, "Choose: ")) {
        msg = 0;
    }

    return msg;
}

int d_create(Table *table)
{
    int size;
    if (get_int(&size, 1, INT_MAX, "Enter table size: ")) {
        return 1;
    }

    create(table, size);

    char *fname = readline("Enter filename: ");
    if (fname == NULL) {
        destroy(table);
        return 1;
    }

    if (import(table, fname)) {
        printf("File not found\n");
    }

    free(fname);

    return 0;
}

int d_insert(Table *table)
{
    int key;
    if (get_int(&key, 0, INT_MAX, "Enter key: ")) {
        return 1;
    }

    char *info = readline("Enter info: ");
    if (info == NULL) {
        return 1;
    }

    int rc = insert(table, key, info);
    if (rc == 1) {
        printf("Key already exists\n");
    } else if (rc == 2) {
        printf("Table is full\n");
    }

    free(info);

    return 0;
}

int d_delete(Table *table)
{
    int key;
    if (get_int(&key, 0, INT_MAX, "Enter key: ")) {
        return 1;
    }

    if (delete(table, key)) {
        printf("Key not found\n");
    }

    return 0;
}

int d_search(Table *table)
{
    int key;
    if (get_int(&key, 0, INT_MAX, "Enter key: ")) {
        return 1;
    }

    char *info;
    if (search(table, key, &info)) {
        printf("Key not found\n");
    } else {
        printf("\"%s\"\n", info);
    }

    return 0;
}

int d_print(Table *table)
{
    print(table);

    return 0;
}

int d_destroy(Table *table)
{
    destroy(table);

    return 0;
}
