#ifndef RBTREE_H
#define RBTREE_H

enum Color {
	RED,
	BLACK
};

typedef struct Info {
    unsigned data;
} Info;

typedef struct Node {
	char *key;
	Info *info;
	enum Color color;
	struct Node *left, *right;
	struct Node *parent;
} Node;

typedef struct Tree {
	Node *root;
} Tree;

Tree* makeTree();

void removeTree(Node *root);

int insertNode(Tree *tree, char *key, unsigned data);

Node* findNode(Tree *tree, char *key);

int deleteNode(Tree *tree, char *key);

int printTreeLikeTree(Tree *tree);

int treeTraversal(Tree *tree);

int import(Tree **tree);

int benchmarkTest(int numberOfTestsPerIteration, int numberOfIterations, int increment, int startValue);

#endif
