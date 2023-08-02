#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dialog.h"

int dialog(const char *msgs[], const int nMsgs){
	int rc = 0, error = 0;
	printf(">>> ");
	error = getInt(&rc);
	if (error == 1)
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
							"\t1) Add new vertex",
							"\t2) Add new edge",
							"\t3) Delete vertex",
							"\t4) Delete edge", 
							"\t5) Change info about vertex", 
							"\t6) Change info about edge",
							"\t7) Print graph",
							"\t8) Breadth first search",
							"\t9) Find minimal distance",
							"\t10) Import"};
	const int nMsgs = sizeof(msgs) / sizeof(msgs[0]);

	int (*fptr[])(Graph **graph) = {NULL, dAddVertex, dAddEdge, dDeleteVertex, dDeleteEdge, dChangeInfoAboutVertex, dChangeInfoAboutEdge, dPrintGraph, dBreadthFirstSearch, dDijkstra, dImport};
	
	Graph *graph = makeGraph();

	int rc, error = 0;

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
			error = fptr[rc](&graph);
			if (!error){
				printf("Success!\n");
			}
			else
				printf("Error!\n");
			error = 0;
		}
	}

	removeGraph(graph);

	return 0;
}
