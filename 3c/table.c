#include "table.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int hash1(int key, int size)
{
    return key % size;
}

int hash2(int key, int size)
{
    return 1 + (key % (size - 1));
}

int find(Table *table, int key)
{
    int i = hash1(key, table->msize);
    int inc = hash2(key, table->msize);
    int count = 0;

    while (count < table->msize && table->ks[i].busy) {
        if (table->ks[i].busy == 1 && table->ks[i].key == key) {
            return i;
        }

        i = (i + inc) % table->msize;
        count++;
    }
    
    return -1;
}

int insert(Table *table, int key, char *info)
{
    if (find(table, key) != -1) {
        return 1;
    }

    int i = hash1(key, table->msize);
    int inc = hash2(key, table->msize);
    int count = 0;

    while (count < table->msize && table->ks[i].busy == 1) {
        i = (i + inc) % table->msize;
        count++;
    }

    if (count == table->msize) {
        return 2;
    }

    table->ks[i].busy = 1;
    table->ks[i].key = key;
    table->ks[i].info = strdup(info);

    return 0;
}

int delete(Table *table, int key)
{
    int i = find(table, key);
    if (i == -1) {
        return 1;
    }

    table->ks[i].busy = -1;
    free(table->ks[i].info);
    table->ks[i].info = NULL;

    return 0;
}

int search(Table *table, int key, char **info)
{
    int i = find(table, key);
    if (i == -1) {
        return 1;
    }

    *info = table->ks[i].info;

    return 0;
}

void print(Table *table)
{
    for (int i = 0; i < table->msize; i++) {
        KeySpace ks = table->ks[i];
        printf("%d %d: \"%s\"\n", ks.busy, ks.key, ks.info);
    }
}

void create(Table *table, int msize)
{
    table->msize = msize;
    table->ks = calloc(table->msize, sizeof(KeySpace));
}

void destroy(Table *table)
{
    for (int i = 0; i < table->msize; i++) {
        if (table->ks[i].busy == 1) {
            free(table->ks[i].info);
        }
    }
    free(table->ks);
}

int import(Table *table, char *fname)
{
    FILE *fd = fopen(fname, "r");
    if (fd == NULL) {
        return 1;
    } 

    while (1) {
        int key;
        if (fget_int(fd, &key, 0, INT_MAX)) {
            break;
        }

        char *info = freadline(fd);
        if (info == NULL) {
            break;
        }

        insert(table, key, info);
        free(info);
    }

    fclose(fd);

    return 0;
}
