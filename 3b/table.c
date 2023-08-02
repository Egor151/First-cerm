#include "table.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int find(Table *table, char *key)
{
    for (int i = 0; i < table->csize; i++) {
        if (table->ks[i].busy && !strcmp(table->ks[i].key, key)) {
            return i;
        }
    }

    return -1;
}

int find_release(Table *table, char *key, int release)
{
    for (int i = 0; i < table->csize; i++) {
        if (table->ks[i].busy && !strcmp(table->ks[i].key, key) && table->ks[i].release == release) {
            return i;
        }
    }

    return -1;
}

void garbage_collection(Table *table)
{
    int j = 0;
    for (int i = 0; i < table->csize; i++)
    {
        if (table->ks[i].busy)
        {
            if (j == i)
            {
                j++;
                continue;
            }

            table->ks[j].busy = 1;
            table->ks[j].key = table->ks[i].key;
            table->ks[j].key_offset = table->ks[i].key_offset;
            table->ks[j].key_len = table->ks[i].key_len;
            table->ks[j].release = table->ks[i].release;
            table->ks[j].info = table->ks[i].info;

            j++;
        }
        table->ks[i].busy = 0;
    }
    table->csize = j;
}

int insert(Table *table, char *key, int info)
{
    if (table->csize == table->msize) {
        garbage_collection(table);
        if (table->csize == table->msize) {
            return 1;
        }
    }

    int release = 1;
    for (int i = table->csize - 1; i >= 0; i--) {
        if (table->ks[i].busy && !strcmp(table->ks[i].key, key)) {
            release = table->ks[i].release + 1;
            break;
        }
    }

    fseek(table->fd, 0, SEEK_END);

    table->ks[table->csize].busy = 1;
    table->ks[table->csize].key = strdup(key);
    table->ks[table->csize].key_offset = ftell(table->fd);
    table->ks[table->csize].key_len = strlen(key);
    table->ks[table->csize].release = release;
    table->ks[table->csize].info = info;

    fwrite(key, sizeof(char), strlen(key), table->fd);
    
    table->csize++;

    return 0;
}

int delete_release(Table *table, char *key, int release)
{
    int i = find_release(table, key, release);
    if (i == -1) {
        return 1;
    }

    table->ks[i].busy = 0;
    free(table->ks[i].key);
    table->ks[i].key = NULL;

    while (i < table->csize) {
        if (table->ks[i].busy && !strcmp(table->ks[i].key, key)) {
            table->ks[i].release--;
        }
        i++;
    }

    return 0;
}

int delete(Table *table, char *key)
{
    int i = find(table, key);
    if (i == -1) {
        return 1;
    }

    while (i < table->csize) {
        if (table->ks[i].busy && !strcmp(table->ks[i].key, key)) {
            table->ks[i].busy = 0;
            free(table->ks[i].key);
            table->ks[i].key = NULL;
        }
        i++;
    }

    return 0; 
}

int search(Table *table, char *key, int release, int *result)
{
    int i = find_release(table, key, release);
    if (i == -1) {
        return 1;
    }

    *result = table->ks[i].info;

    return 0;
}

void print(Table *table)
{
    for (int i = 0; i < table->csize; i++) {
        KeySpace ks = table->ks[i];
        printf("%d \"%s\" (%d): %d\n", ks.busy, ks.key, ks.release, ks.info);
    }
}

void create(Table *table, char *fname, int msize)
{
    FILE *fd = fopen(fname, "w+b");

    table->fd = fd;
    table->msize = msize;
    table->csize = 0;
    table->ks = calloc(table->msize, sizeof(KeySpace));

    fwrite(&table->msize, sizeof(int), 1, table->fd);
    fwrite(&table->csize, sizeof(int), 1, table->fd);

    for (int i = 0; i < table->msize; i++) {
        fwrite(&table->ks[i].busy, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].key_offset, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].key_len, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].release, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].info, sizeof(int), 1, table->fd);
    }
}

int load(Table *table, char *fname)
{
    FILE *fd = fopen(fname, "r+b");
    if (fd == NULL) {
        return 1;
    }

    table->fd = fd;
    fread(&table->msize, sizeof(int), 1, table->fd);
    fread(&table->csize, sizeof(int), 1, table->fd);

    table->ks = calloc(table->msize, sizeof(KeySpace));

    for (int i = 0; i < table->csize; i++) {
        fread(&table->ks[i].busy, sizeof(int), 1, table->fd);
        fread(&table->ks[i].key_offset, sizeof(int), 1, table->fd);
        fread(&table->ks[i].key_len, sizeof(int), 1, table->fd);
        fread(&table->ks[i].release, sizeof(int), 1, table->fd);
        fread(&table->ks[i].info, sizeof(int), 1, table->fd);

        if (!table->ks[i].busy) {
            continue;
        }

        int offset = ftell(table->fd);

        table->ks[i].key = calloc(table->ks[i].key_len + 1, sizeof(char));
        fseek(table->fd, table->ks[i].key_offset, SEEK_SET);
        fread(table->ks[i].key, sizeof(char), table->ks[i].key_len, table->fd);

        fseek(table->fd, offset, SEEK_SET);
    }

    return 0;
}

int import(Table *table, char *fname)
{
    FILE *fd = fopen(fname, "r");
    if (fd == NULL) {
        return 1;
    } 

    while (1) {
        char *key = freadline(fd);
        if (key == NULL) {
            break;
        }

        int info;
        if (fget_int(fd, &info, 0, INT_MAX)) {
            free(key);
            break;
        }

        insert(table, key, info);
        free(key);
    }

    fclose(fd);

    return 0;
}

void save(Table *table)
{
    fseek(table->fd, sizeof(int), SEEK_SET);
    fwrite(&table->csize, sizeof(int), 1, table->fd);

    for (int i = 0; i < table->csize; i++) {
        fwrite(&table->ks[i].busy, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].key_offset, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].key_len, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].release, sizeof(int), 1, table->fd);
        fwrite(&table->ks[i].info, sizeof(int), 1, table->fd);
        
        if (table->ks[i].busy) {
            free(table->ks[i].key);
        }
    }

    free(table->ks);
    fclose(table->fd);
}
