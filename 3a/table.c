#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void swap_key_ptrs(KeySpace *el1, KeySpace *el2) {
    KeySpace tmp = *el1;
    *el1 = *el2;
    *el2 = tmp;
}

void free_element(KeySpace *element) {
    if (!element) return ;

    if (!element->info) return ;
    if (!element->key) return ;

    free(element->info->data);
    free(element->info);
    free(element->key);

    element->key = NULL;
    element->info = NULL;
}

void print_element(KeySpace *element) {
    if (!element) return ;

    if (!element->info) return ;
    if (!element->key) return ;
    if (!(element->info->data)) return ;

    printf("%d\t", element->busy);
    printf("%s\t", element->key);
    printf("%d\t", element->release);
    printf("%d\n", *(element->info->data));

}

int garbage_collection(Table *table) {
    if (!table) return 1;

    
    int new_size = 0;
    KeySpace *cur_ptr;

    for (int i = 0; i < table->csize; i++) {
        cur_ptr = table->ks + i;
        if (cur_ptr->busy != 0) {
            swap_key_ptrs(table->ks + new_size, cur_ptr);
            new_size += 1;
        } else {
        	free_element(cur_ptr);
        }
    }

    if (new_size == 0) { 
    	free(table->ks);
    	table->ks = NULL;
    	table->csize = 0;
    	return 0;
    }


    table->ks = realloc(table->ks, sizeof(KeySpace) * new_size);
    table->csize = new_size;

    return 1;
}

int find(Table *table, char *key, int release, int *save) {
    if (!table) return -1;

    if(!table->ks) return -1;

    if (!key) return -1;

    KeySpace *cur_element;
    for(int i = *save; i < table->csize; i++) {
        cur_element = table->ks + i;
        if (cur_element->busy != 0) {
            if (release != -1) {
                if(!strcmp(key, cur_element->key) && (cur_element->release == release)) {
                    *save = i + 1;
                    return i;
                }
            }
            else {
                if (!strcmp(key, cur_element->key)) {
                    *save = i + 1;
                    return i;
                }
            }

        }
    }

    return -1;
}

int delete(Table *table, char *key, int release) {
    if (!table) return -1;

    if (!table->ks) return -1;

    int save = 0;
    int idx;
    while ((idx = find(table, key, release, &save)) != -1) {
        KeySpace *cur_element = table->ks + idx;
        cur_element->busy = 0;
    }

    return 0;
}

int insert(Table *table, char *key, int data) {
    if (!table) return -1;

    if (data < 0) {
    	printf("Error: data must be non-negative\n");
    	return -1;
    }

    if (table->csize == table->msize) {
        if (!garbage_collection(table)) return -1;
    }

    if (table->csize >= table->msize) {
    	printf("Error: Table is full\n");
    	return -1;
    }

    int release = 0;
    if (table->ks != NULL) {
        int save = 0;
        int idx;
        while((idx = find(table, key, -1, &save)) != -1) {
            release = (table->ks + idx)->release;
        }

    }

    table->ks = realloc(table->ks, (++table->csize) * sizeof(KeySpace));
    KeySpace *elem_insert = table->ks + table->csize - 1;

    elem_insert->busy = 1;
    elem_insert->release = release + 1;
    elem_insert->key = key;

    Item *item_insert = calloc(1, sizeof(Item));
    item_insert->data = calloc(1, sizeof(int));
    *(item_insert->data) = data;

    elem_insert->info = item_insert;

    return 0;
}
