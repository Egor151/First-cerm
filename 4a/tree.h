#ifndef TREE_H
#define TREE_H

typedef struct ListNode
{
    int info;
    struct ListNode *next;
}
ListNode;

typedef struct TreeNode
{
    int is_thread;
    char *key;
    ListNode *data;
    struct TreeNode *left;
    struct TreeNode *right;
}
TreeNode;

typedef struct Tree
{
    TreeNode *root;
}
Tree;

int insert(Tree *tree, char *key, int info);
int delete(Tree *tree, char *key, int release);

int search(Tree *tree, char *key, int release, int *info);
TreeNode *special(Tree *tree, char *max_key);

void print_node(TreeNode *node);
void walk(Tree *tree, char *min_key);
void print(TreeNode *node, int prefix);

void create(Tree *tree);
void destroy(TreeNode *node);

int import(Tree *tree, char *fname);

#endif // TREE_H
