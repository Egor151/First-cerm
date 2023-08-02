#ifndef TABLE_H
#define TABLE_H

typedef struct Item {
   unsigned int *data;
} Item;

typedef struct KeySpace {
    int busy;
    int release;
    char *key;
    Item *info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
} Table;

void swap_key_ptrs(KeySpace *el1, KeySpace *el2);

void free_element(KeySpace *element);
void print_element(KeySpace *element);

int garbage_collection(Table *table);

int find(Table *table, char *key, int release, int *save);
int delete(Table *table, char *key, int release);
int insert(Table *table, char *key, int data);

#endif // TABLE_H
