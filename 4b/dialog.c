#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>

#include "dialog.h"
#include "RBTree.h"

#define EList &leaf_E
Node leaf_E = { NULL, NULL, BLACK, EList, EList, EList};

int getUnsignedInt(unsigned *n){
	char trash[80];
	int code;
	long long int tmp;
	do{
		code = scanf("%lld", &tmp);
		if (code == -1)
			return 1;
		if (code == 0 || tmp < 0 || tmp > UINT_MAX){
			printf("Incorrect input data!\n");
			scanf("%*c", trash);
			continue;
		}
		else{
			(*n) = (unsigned) tmp;
			break;
		}
	} while (1);

	return 0;
}

int dAddNode(Tree **tree){
	char *key;
	unsigned data;
	int error = 0;

	key = readline("Input key (string): ");
	if (key == NULL)
		return 1;

	printf("Input info (integer): ");
	error = getUnsignedInt(&data);
	if (error){
		free(key);
		return error;
	}

	return insertNode(*tree, key, data);
}

int dDeleteNode(Tree **tree){
	char *key;
	int error;

	key = readline("Input key (string): ");
	if (key == NULL)
		return 1;

	error = deleteNode(*tree, key);
	free(key);

	return error;
} 

int dFindNode(Tree **tree){
	char *key;

	key = readline("Input key (string): ");
	if (key == NULL)
		return 1;

	Node *foundNode = findNode(*tree, key);
	if (foundNode == NULL || foundNode == EList){
		printf("No such element\n");
		free(key);
		return 1;
	}
	free(key);

	printf("Key: %s\n", foundNode->key);
	printf("Info: %u\n", foundNode->info->data);
	if (foundNode->color == RED)
		printf("Color: RED\n");
	else
		printf("Color: BLACK\n");

	return 0;
}

int dPrintTree(Tree **tree){

	int error = printTreeLikeTree(*tree);
	if (error)
		printf("Tree is empty\n");

	return error;
}

int dTreeTraversal(Tree **tree){

	int error = treeTraversal(*tree);
	if (error)
		printf("Tree is empty\n");

	return error;
}

int dImport(Tree **tree){
	return import(tree);
}

int dBenchmarkTest(Tree **tree){
    int error = benchmarkTest(10, 10, 5000, 5000);

	return error;
}
