#include <stdio.h>
#include <stdlib.h>

#include "dialog.h"
#include "RBTree.h"

int getInt(int *digit){
	int errorCode = 0;
	char trash[81];

	do{
		errorCode = scanf("%d", digit);
		if (errorCode == -1) 
			return 1;
		if (errorCode == 0){
			printf("Incorrect input data!\n");
			scanf("%*c", trash);
			continue;
		}

	} while(errorCode != 1);

	return 0;
}

int dialog(const char *msgs[], const int nMsgs){
	int rc = 0, errorCode = 0;
	printf(">>> ");
	errorCode = getInt(&rc);
	if (errorCode == 1)
		return 0;
	for(int i = 0; i < nMsgs - 1; i++){
		if (i == rc)
			return i;
	}

	return -1;
}

void printMsgs(const char *msgs[], const int nMsgs){
	for(int i = 0; i < nMsgs; i++)
		printf("%s\n", msgs[i]);
}

int main(){
	const char *msgs[] = {	"Commands:",
							"\t0) Exit",
							"\t1) New node",
							"\t2) Delete", 
							"\t3) Find", 
							"\t4) Print tree like tree",
							"\t5) RB tree traversal",
							"\t6) Import",
							"\t7) Benchmark test",};
	const int nMsgs = sizeof(msgs) / sizeof(msgs[0]);

	int (*fptr[])(Tree **tree) = {NULL, dAddNode, dDeleteNode, dFindNode, dPrintTree, dTreeTraversal, dImport, dBenchmarkTest};

	Tree *tree = makeTree();

	int rc, errorCode = 0;

	while(1){
		printMsgs(msgs, nMsgs);
		rc = dialog(msgs, nMsgs);
		if (rc == 0)
			break;
		else if (rc == -1){
			printf("No such command!\n");
			continue;
		}
		else{
			errorCode = fptr[rc](&tree);
			if (!errorCode){
				printf("Success!\n");
			}
			else
				printf("Error!\n");
			errorCode = 0;
		}
	}

	removeTree(tree->root);
	free(tree);

	return 0;
}
