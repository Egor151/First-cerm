#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include "dialog.h"
#include "graph.h"

int getInt(int *digit){
	int error = 0;
	char trash[81];

	do{
		error = scanf("%d", digit);
		if (error == -1) 
			return 1;
		if (error == 0){
			printf("Incorrect input data!\n");
			scanf("%*c", trash);
			continue;
		}

	} while(error != 1);

	return 0;
}

int dAddVertex(Graph **graph){
	char *name;

	name = readline("Enter the name (string): ");
	if (name == NULL)
		return 1;

	int error = addVertex(*graph, name);

	return error;
}

int dAddEdge(Graph **graph){
	char *from, *to;
	int grade;

	from = readline("Enter the first (from) name (string): ");
	if (from == NULL)
		return 1;

	to = readline("Enter the second (to) name (string): ");
	if (to == NULL) {
		free(from);
		return 1;
	}

	printf("Enter the grade (integer, -10 <= x <= 10): ");
	int error = getInt(&grade);
	if (error || grade > 10 || grade < -10){
		free(from);
		free(to);
		return 1;
	}

	error = addEdge(*graph, from, to, grade);
	free(from);
	free(to);

	return error;
} 

int dDeleteVertex(Graph **graph){
	char *name;

	name = readline("Enter the name to delete (string): ");
	if (name == NULL)
		return 1;

	int error = deleteVertex(*graph, name);
	free(name);

	return 0;
}

int dDeleteEdge(Graph **graph){
	char *from, *to;

	from = readline("Enter the first name (string): ");
	if (from == NULL)
		return 1;

	to = readline("Enter the second name (string): ");
	if (to == NULL){
		free(from);
		return 1;
	}

	int error = deleteEdge(*graph, from, to);
	free(from);
	free(to);

	return error;
}

int dChangeInfoAboutVertex(Graph **graph){
	char *oldName, *newName;

	oldName = readline("Enter the old name of vertex (string): ");
	if (oldName == NULL)
		return 1;

	newName = readline("Enter the new name of vertex (string): ");
	if (newName == NULL){
		free(oldName);
		return 1;
	}

	int error = changeInfoAboutVertex(*graph, oldName, newName);
	free(oldName);
	if (error)
		free(newName);

	return error;
}

int dChangeInfoAboutEdge(Graph **graph){
	char *from, *oldTo, *newTo;
	int grade;

	from = readline("Enter the old first (from) name (string): ");
	if (from == NULL)
		return 1;

	oldTo = readline("Enter the old second (to) name (string): ");
	if (oldTo == NULL){
		free(from);
		return 1;
	}

	newTo = readline("Enter the new second (to) name (string): ");
	if (newTo == NULL){
		free(from);
		free(oldTo);
		return 1;
	}

	printf("Enter new grade: ");
	int error = getInt(&grade);
	if (error){
		free(from);
		free(oldTo);
		free(newTo);
		return 1;
	}

	error = changeInfoAboutEdge(*graph, from, oldTo, newTo, grade);
	free(from);
	free(oldTo);
	free(newTo);

	return error;
}

int dPrintGraph(Graph **graph){
    int error = printGraph(*graph);

    return error;
}

int dBreadthFirstSearch(Graph **graph){
	char *name = readline("Enter the name (string): ");
	if (name == NULL)
		return 1;

	int n;	// Количество рукопожатий
	printf("Enter the number of handshakes: ");
	int error = getInt(&n);
	if (error){
		free(name);
		return 1;
	}

	char **names = breadthFirstSearch(*graph, name, n);
	free(name);
	if (names == NULL)
		return 1;
	for(int i = 0; i < (*graph)->size; i++){
		if (names[i] == NULL)
			break;
		printf("\"%s\"\n", names[i]);
		free(names[i]);
	}
	free(names);

	return 0;
}

int dDijkstra(Graph **graph){
	char *from, *to;

	from = readline("Enter the first (from) name (string): ");
	if (from == NULL)
		return 1;

	to = readline("Enter the second (to) name (string): ");
	if (to == NULL){
		free(from);
		return 1;
	}

	int error = dijkstra(*graph, from, to);

	free(from);
	free(to);

	return error;
}

int dImport(Graph **graph){
	int error = importData(graph);
	return error;
}
