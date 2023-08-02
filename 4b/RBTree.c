#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <time.h>

#include "RBTree.h"

#define EList &leaf
Node leaf = { NULL, NULL, BLACK, EList, EList, EList};

Tree* makeTree(){
    Tree *tree = calloc(1, sizeof(Tree));
    tree->root = EList;
    return tree;
}

void removeTree(Node *root){
    if (root != EList){
        removeTree(root->left);
        removeTree(root->right);
        free(root->key);
        free(root->info);
        free(root);
    }
}

void rotateLeft(Tree *tree, Node *x) {
    Node *y = x->right;

    x->right = y->left;
    if (y->left != EList) y->left->parent = x;

    if (y != EList)
        y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else 
        tree->root = y;

    y->left = x;
    if (x != EList)
        x->parent = y;
}

void rotateRight(Tree *tree, Node *x) {
    Node *y = x->left;

    x->left = y->right;
    if (y->right != EList) y->right->parent = x;

    if (y != EList)
        y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else
        tree->root = y;


    y->right = x;
    if (x != EList)
        x->parent = y;
}

void insertFixup(Tree *tree, Node *x) {
    while (x != tree->root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(tree, x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(tree, x->parent->parent);
            }
        } else {

            Node *y = x->parent->parent->left;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(tree, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(tree, x->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

int insertNode(Tree *tree, char *key, unsigned data) {
    Node *new = calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;
    new->left = EList;
    new->right = EList;
    new->parent = EList;
    new->key = key;
    new->info = calloc(1, sizeof(Info));
    if (new->info == NULL)
        return 1;
    new->info->data = data;

    Node *foundNode = findNode(tree, key);
    if (foundNode != NULL){
        // printf("Old key: %s\n", foundNode->key);
        // printf("Old info: %u\n", foundNode->info->info);
        foundNode->info->data = data;
        free(new->info);
        free(new->key);
        free(new);

        return 0;
    }

    new->color = RED;
    Node *current = tree->root, *parent = NULL;
    while(current != EList){
        parent = current;
        if (strcmp(key, current->key) < 0)
            current = current->left;
        else
            current = current->right;
    }

    new->parent = parent;

    if(parent) {
        if (strcmp(key, parent->key) < 0)
            parent->left = new;
        else
            parent->right = new;
    } else 
        tree->root = new;

    insertFixup(tree, new);

    return 0;
}

Node* findNode(Tree *tree, char *key){
    Node *tmp = tree->root;

    while(tmp != EList){
        if (strcmp(key, tmp->key) == 0)
            return tmp;
        else if (strcmp(key, tmp->key) < 0)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }

    return NULL;
}

void deleteFixup(Tree *tree, Node *x){
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

int deleteNode(Tree *tree, char *key){
    Node *x, *y, *z = findNode(tree, key);

    if (!z || z == EList)
        return 1;


    if (z->left == EList || z->right == EList)
        y = z;
    else {
        y = z->right;
        while (y->left != EList) 
            y = y->left;
    }

    if (y->left != EList)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        tree->root = x;

    if (y != z){
        free(z->key);
        z->key = strdup(y->key);
    }

    if (y->color == BLACK)
        deleteFixup(tree, x);

    free(y->info);
    free(y->key);
    free(y);

    return 0;
}

void printTreeLikeTreeRecursion(Node *root, int n){
    if (root->right != EList)
        printTreeLikeTreeRecursion(root->right, n + 1);

    for(int i = 0; i < n; i++){
        if (i == n - 1)
            printf("     ");
        else
            printf("     ");
    }
    if (root->color == RED)
        printf("{%s}[RED]\n", root->key);
    else
        printf("{%s}[BLACK]\n", root->key);

    if (root->left != EList)
        printTreeLikeTreeRecursion(root->left, n + 1);
}

int printTreeLikeTree(Tree *tree){
	if (tree->root == EList)
		return 1;

	printTreeLikeTreeRecursion(tree->root, 0);

	return 0;
}

void endBypass(Node *root){
	if (root != EList) {
		endBypass(root->left);
		endBypass(root->right);
		printf("Key: %s\n", root->key);
		printf("Info: %u\n", root->info->data);
		printf("--------\n");
	}
}

int treeTraversal(Tree *tree){
	if (tree->root == EList)
		return 1;

	endBypass(tree->root);

	return 0;
}

int import(Tree **tree){
	if ((*tree)->root != NULL){
		removeTree((*tree)->root);
		free(*tree);
	}
	else
		free(*tree);

	FILE *file;
	char str[50];
	char *estr, *data = NULL;
	int i = 0, errorCode = 0;;

	file = fopen("treeDATA.txt", "r");
	if (!file){
		printf("Can't open file!\n");
		return 1;
	}

	unsigned int info;
	char *key;
	(*tree) = makeTree();

	while(!feof(file)){
		estr = fgets(str, sizeof(str), file);
		if (estr == NULL)
			break;
		key = data;
		data = strdup(str);
		data[strlen(data) - 1] = '\0';
		if (i++ % 2 != 0){
			info = (unsigned)atoi(data);
			free(data);
			insertNode(*tree, key, info);
		}
	}
	free(estr);
	fclose(file);

	return 0;
}

char* generateWord(){
	int size = (2 + rand() % 9);
	char *word = calloc(size, sizeof(char));
	for(int i = 0; i < size - 1; i++){
		word[i] = (char)(97 + rand() % 26);
	}
	word[size - 1] = '\0';
	//printf("%s\n", word);
	return word;
}

int benchmarkTest(int counter2, int counter1, int increment, int startValue){

	clock_t startAdd = 0, endAdd = 0, startFind = 0, endFind = 0, startDelete = 0, endDelete = 0;
	clock_t averageAdd = 0, averageFind = 0, averageDelete = 0;

	int errorCode = 0;
	for(int i = 0; i < counter1; i++){
		srand(time(NULL));
		for(int j = 0; j < counter2; j++){
			Tree *tree = makeTree();

			startAdd = clock();
			for(int k = 0; k < startValue; k++){
				char *key = generateWord();
				unsigned data = (unsigned)(rand() % startValue);
				errorCode = insertNode(tree, key, data);
				if (errorCode)
					return 1;
			}
			endAdd = clock();
			averageAdd += (endAdd - startAdd);

			startFind = clock();
			for(int k = 0; k < startValue; k++){
				char *key = generateWord();
				Node *a = findNode(tree, key);
				free(key);
			}
			endFind = clock();
			averageFind += (endFind - startFind);

			startDelete = clock();
			for(int k = 0; k < startValue; k++){
				char *key = generateWord();
				deleteNode(tree, key);
				free(key);
				// if (errorCode)
				// 	printf("ERROR!\n");
			}
			endDelete = clock();
			averageDelete += (endDelete - startDelete);

			removeTree(tree->root);
			free(tree);
		}
		printf("-----------------------------------------\n");
		printf("Time to add (%d elements) - %lf\n", startValue, (double)(averageAdd / counter1) / CLOCKS_PER_SEC);
		printf("Time to search (%d elements) - %lf\n", startValue, (double)(averageFind / counter1) / CLOCKS_PER_SEC);
		printf("Time to delete (%d elements) - %lf\n", startValue, (double)(averageDelete / counter1) / CLOCKS_PER_SEC);

		startValue += increment;
	}

	return 0;
}
