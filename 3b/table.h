#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

typedef struct KeySpace {
    int busy;
    char *key;
    int key_offset;
    int key_len;
    int release;
    int info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
    FILE *fd;
} Table;

int find(Table *table, char *key);
int find_release(Table *table, char *key, int release);

void garbage_collection(Table *table);
int insert(Table *table, char *key, int info);

int delete_release(Table *table, char *key, int release);
int delete(Table *table, char *key);

int search(Table *table, char *key, int release, int *result);

void print(Table *table);

void create(Table *table, char *fname, int msize);
int load(Table *table, char *fname);
int import(Table *table, char *fname);
void save(Table *table);

#endif // TABLE_H
