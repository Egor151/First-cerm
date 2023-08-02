#include "dialog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* readline(char* message) {
    printf("%s", message);

    char buffer[BUFFER_SIZE + 1] = {0};
    char* res = NULL;
    int len = 0;
    int n;

    do {
        n = scanf("%80[^\n]", buffer);
        if (n < 0 ) {
            return NULL;
        }
        else if (n > 0) {
            int chunk_len = strlen(buffer);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buffer, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }

    return res;
}


int get_int(int *res, char *msg) {
    char *buf = readline(msg);
    if (!buf) {
        return 0;
    }

    int tmp = atoi(buf);
    if (tmp == 0) {
        free(buf);
        return 0;
    }

    *res = tmp;
    free(buf);
    return 1;
}

int dialog(const char *msgs[], int N)
{
    char *errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeate, please!";
        for(i = 0; i < N; ++i)
            puts(msgs[i]);

        n = get_int(&rc, "Make your choice: --> ");
        if(n == 0)
            rc = 0;
    } while(rc < 0 || rc >= N);
    return rc;
}

int d_insert(Table *table) {
    if (!table) return -1;

    char *key = readline("Enter key: --> ");
    if (!key) return -1;

    if (key[0] == '\0') {
        printf("Insertion error!\n");
        free(key);
        return -1;
    }

    int data = 0;
    if (!get_int(&data, "Enter value: --> ")) {
        printf("Insertion error!\n");
        free(key);
        return -1;
    }

    if (insert(table, key, data)) {
        printf("Insertion error!\n");
        free(key);
        return -1;
    }

    return 1;
}

int d_delete(Table *table) {
    if (!table) return -1;

    char *key = readline("Enter key --> ");
    if (!key) return -1;

    printf("If you want to delete without release, put in -1\n");

    int release = 0, status = get_int(&release, "Now type in the release: ");
    if (status == 0) {
        free(key);
        printf("Deletion error!\n");
        return -1;
    }

    if (delete(table, key, release)) {
        printf("Deletion error!\n");
        free(key);
        return -1;
    }

    free(key);
    return 1;
}

int d_find(Table *table) {
    char *key = readline("Enter key --> ");
    if (!key) return -1;
    printf("If you want to find without release, put in 1\n");

    int release = 0, status = get_int(&release, "Now type in the release: ");
    if (status == 0) {
        free(key);
        printf("Print error!\n");
        return -1;
    }

    printf("Busy\tKey\tRelease\tData\n");
    int save = 0;
    int idx = find(table, key, -1, &save);
    while(idx != -1) {
        print_element(table->ks + idx);
        idx = find(table, key, -1, &save);
    }

    free(key);
    return 1;
}

int d_print(Table *table) {
    printf("Busy\tKey\tRelease\tData\n");
    for (int i = 0; i < table->csize; i++) {
        print_element(table->ks + i);
    }

    return 1;
}

int d_garbage_collection(Table *table) {
    int status = garbage_collection(table);
    if (!status) {
        printf("Garbage collection error!\n");
        return -1;
    }

    return 1;
}
