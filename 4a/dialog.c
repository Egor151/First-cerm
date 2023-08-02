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

int d_create(Tree *tree)
{
    create(tree);

    char *fname = readline("Enter filename: ");
    if (fname == NULL) {
        return 1;
    }

    if (import(tree, fname)) {
        printf("File not found\n");
    }

    free(fname);

    return 0;
}

int d_insert(Tree *tree)
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

    insert(tree, key, info);

    free(key);

    return 0;
}

int d_delete(Tree *tree)
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

    if (delete(tree, key, release)) {
        printf("Item not found\n");
    }

    free(key);

    return 0;
}

int d_search(Tree *tree)
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
    if (search(tree, key, release, &info)) {
        printf("Item not found\n");
    } else {
        printf("%d\n", info);
    }

    free(key);

    return 0;
}

int d_special(Tree *tree)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    TreeNode *res = special(tree, key);
    if (res == NULL) {
        printf("Item not found\n");
    } else {
        print_node(res);
    }

    free(key);

    return 0;
}

int d_walk(Tree *tree)
{
    char *key = readline("Enter key: ");
    if (key == NULL) {
        return 1;
    }

    if (*key == '\0')
        walk(tree, NULL);
    else
        walk(tree, key);

    free(key);

    return 0;
}

int d_print(Tree *tree)
{
    print(tree->root, 0);

    return 0;
}

int d_destroy(Tree *tree)
{
    destroy(tree->root);

    return 0;
}
