#include "tree.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int insert(Tree *tree, char *key, int info)
{
    TreeNode *ptr = tree->root;
    TreeNode *par = NULL;

    while (ptr != NULL)
    {
        if (!strcmp(key, ptr->key))
        {
            ListNode *new = malloc(sizeof(ListNode));

            new->info = info;
            new->next = ptr->data;
            ptr->data = new;

            return 0;
        }

        par = ptr;
        
        if (strcmp(key, ptr->key) < 0)
            ptr = ptr->left;
        else if (!ptr->is_thread)
            ptr = ptr->right;
        else
            break;
    }

    TreeNode *new = calloc(1, sizeof(TreeNode));

    new->is_thread = 1;
    new->key = strdup(key);
    new->data = calloc(1, sizeof(ListNode));
    new->data->info = info;

    if (par == NULL)
        tree->root = new;
    else if (strcmp(key, par->key) < 0)
    {
        new->right = par;
        par->left = new;
    }
    else
    {
        new->right = par->right;
        par->right = new;
        par->is_thread = 0;
    }

    return 0;
}

int delete(Tree *tree, char *key, int release)
{
    TreeNode *ptr = tree->root;
    TreeNode *par = NULL;

    while (ptr != NULL)
    {
        if (!strcmp(key, ptr->key))
        {
            ListNode *curr = ptr->data;
            ListNode *prev;
            int count = 1;

            while (curr != NULL && count != release)
            {
                prev = curr;
                curr = curr->next;
                count++;
            }

            if (curr == NULL)
                return 1;
            
            if (curr == ptr->data)
                ptr->data = curr->next;
            else
                prev->next = curr->next;
            
            free(curr);

            if (ptr->data == NULL)
                break;

            return 0;
        }

        par = ptr;

        if (strcmp(key, ptr->key) < 0)
            ptr = ptr->left;
        else if (!ptr->is_thread)
            ptr = ptr->right;
        else
            return 1;
    }

    if (ptr == NULL)
        return 1;

    if (ptr->is_thread)
    {
        if (ptr->left != NULL)
        {
            TreeNode *pred = ptr->left;
            while (!pred->is_thread)
                pred = pred->right;
            pred->right = ptr->right;
            
            if (par == NULL)
                tree->root = ptr->left;
            else if (ptr == par->left)
                par->left = ptr->left;
            else
                par->right = ptr->left;
        }
        else
        {
            if (par == NULL)
                tree->root = ptr->left;
            else if (ptr == par->left)
                par->left = ptr->left;
            else
            {
                par->right = ptr->right;
                par->is_thread = 1;
            }
        }
    } 
    else
    {
        TreeNode *right = ptr->right;
        if (right->left == NULL)
        {
            right->left = ptr->left;
            if (right->left != NULL)
            {
                TreeNode *pred = right->left;
                while (!pred->is_thread)
                    pred = pred->right;
                pred->right = right;
            }

            if (par == NULL)
                tree->root = right;
            else if (ptr == par->left)
                par->left = right;
            else
                par->right = right;
        }
        else
        {
            TreeNode *succ = right->left;
            while (succ->left != NULL)
            {
                right = succ;
                succ = succ->left;
            }

            if (succ->is_thread)
                right->left = NULL;
            else
                right->left = succ->right;

            succ->left = ptr->left;
            if (succ->left != NULL)
            {
                TreeNode *pred = succ->left;
                while (!pred->is_thread)
                    pred = pred->right;
                pred->right = succ;
            }

            succ->right = ptr->right;
            succ->is_thread = 0;

            if (par == NULL)
                tree->root = succ;
            else if (ptr == par->left)
                par->left = succ;
            else
                par->right = succ;
        }
    }

    free(ptr->key);
    free(ptr);

    return 0;
}

int search(Tree *tree, char *key, int release, int *info)
{
    TreeNode *ptr = tree->root;

    while (ptr != NULL)
    {
        if (!strcmp(key, ptr->key))
        {
            ListNode *curr = ptr->data;
            int count = 1;

            while (curr != NULL && count != release)
            {
                curr = curr->next;
                count++;
            }

            if (curr == NULL)
                return 1;

            *info = curr->info;

            return 0;
        }

        if (strcmp(key, ptr->key) < 0)
            ptr = ptr->left;
        else if (!ptr->is_thread)
            ptr = ptr->right;
        else
            return 1;
    }

    return 1;
}

TreeNode *special(Tree *tree, char *max_key)
{
    TreeNode *ptr = tree->root;
    TreeNode *res = NULL;

    while (ptr != NULL)
    {
        if (strcmp(ptr->key, max_key) < 0)
        {
            res = ptr;
            
            if (ptr->is_thread)
                break;
            
            ptr = ptr->right;
        }
        else
        {
            ptr = ptr->left;
        }
    }

    return res;
}

void print_node(TreeNode *node)
{
    printf("\"%s\": {", node->key);

    ListNode *curr = node->data;
    while (curr != NULL)
    {
        printf("%d", curr->info);
        curr = curr->next;
        if (curr != NULL)
            printf(", ");
    }

    printf("}\n");
}

void walk(Tree *tree, char *min_key)
{
    if (tree->root == NULL)
        return;

    TreeNode *ptr = tree->root;
    while (ptr->left != NULL)
        ptr = ptr->left;

    while (ptr != NULL)
    {
        if (min_key == NULL || strcmp(ptr->key, min_key) > 0)
            print_node(ptr);

        if (ptr->is_thread)
            ptr = ptr->right;
        else
        {
            ptr = ptr->right;
            while (ptr->left != NULL)
                ptr = ptr->left;
        }
    }
}

void print(TreeNode *node, int prefix)
{
    if (node == NULL)
        return;

    if (!node->is_thread)
        print(node->right, prefix + 8);

    for (int i = 0; i < prefix; i++)
        printf(" ");
    print_node(node);

    print(node->left, prefix + 8);
}

void create(Tree *tree)
{
    tree->root = NULL;
}

void destroy(TreeNode *node)
{
    if (node == NULL)
        return;

    if (!node->is_thread)
        destroy(node->right);
    destroy(node->left);

    ListNode *curr = node->data, *prev;
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(node->key);
    free(node);
}

int import(Tree *tree, char *fname)
{
    FILE *fd = fopen(fname, "r");
    if (fd == NULL)
        return 1;

    while (1)
    {
        char *key = freadline(fd);
        if (key == NULL)
            break;

        int info;
        if (fget_int(fd, &info, 0, INT_MAX))
        {
            free(key);
            break;
        }

        insert(tree, key, info);
        free(key);
    }

    fclose(fd);

    return 0;
}
