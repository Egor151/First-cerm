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

int d_load(Table *table)
{
    char *fname = readline("Enter filename: ");
    if (fname == NULL) {
        return 1;
    }

    if (load(table, fname)) {
        printf("File not found\n");

        int size;
        if (get_int(&size, 1, INT_MAX, "Enter table size: ")) {
            free(fname);
            return 1;
        }

        create(table, fname, size);
        free(fname);

        fname = readline("Enter filename to import from: ");
        if (fname == NULL) {
            save(table);
            return 1;
        }

        if (import(table, fname)) {
            printf("File not found\n");
        }
    }

    free(fname);

    return 0;
}

int d_insert(Table *table)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    int info;
    if (get_int(&info, 0, INT_MAX, "Enter info: ")) {
        free(key);
        return 1;
    }

    if (insert(table, key, info)) {
        printf("Table is full\n");
    }

    free(key);

    return 0;
}

int d_delete_release(Table *table)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    int release;
    if (get_int(&release, 1, INT_MAX, "Enter release: ")) {
        free(key);
        return 1;
    }

    if (delete_release(table, key, release)) {
        printf("Release not found\n");
    }

    free(key);

    return 0;
}

int d_delete(Table *table)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    if (delete(table, key)) {
        printf("Key not found\n");
    }

    free(key);

    return 0;
}

int d_search(Table *table)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    int release;
    if (get_int(&release, 1, INT_MAX, "Enter release: ")) {
        free(key);
        return 1;
    }

    int info;
    if (search(table, key, release, &info)) {
        printf("Info not found\n");
    } else {
        printf("%d\n", info);
    }

    free(key);

    return 0;
}

int d_print(Table *table)
{
    print(table);

    return 0;
}

int d_garbage_collection(Table *table)
{
    garbage_collection(table);

    return 0;
}

int d_save(Table *table)
{
    save(table);

    return 0;
}
