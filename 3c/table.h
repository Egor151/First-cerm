#ifndef TABLE_H
#define TABLE_H

typedef struct KeySpace {
    int busy;
    int key;
    char *info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
} Table;

int hash1(int key, int size);
int hash2(int key, int size);

int find(Table *table, int key);

int insert(Table *table, int key, char *info);

int delete(Table *table, int key);

int search(Table *table, int key, char **info);

void print(Table *table);

void create(Table *table, int msize);
void destroy(Table *table);

int import(Table *table, char *fname);

#endif // TABLE_H
