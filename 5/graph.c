#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"

Graph *makeGraph() {
	Graph *graph = calloc(1, sizeof(Graph));
	graph->size = 0;
	graph->vertices = NULL;
	return graph;
}

void removeGraph(Graph *graph){
	for(int i = 0; i < graph->size; i++){
		free(graph->vertices[i].name);
		if (graph->vertices[i].edges != NULL)
			free(graph->vertices[i].edges);
	}
	if (graph->vertices != NULL)
		free(graph->vertices);
	free(graph);
}

int addVertex(Graph *graph, char *name){
	for(int i = 0; i < graph->size; i++){
		if (strcmp(graph->vertices[i].name, name) == 0){
			printf("Dublicate of names!\n");
			return 1;
		}
	}

	if (graph->size == 0){
		graph->vertices = calloc(1, sizeof(Vertex));
		if (graph->vertices == NULL)
			return 1;
	}
	else {
		graph->vertices = realloc(graph->vertices, (graph->size + 1) * sizeof(Vertex));
		if (graph->vertices == NULL)
			return 1;
	}
	graph->vertices[graph->size].name = name;
	graph->vertices[graph->size].count = 0;
	graph->vertices[graph->size].edges = NULL;
	graph->size++;

	return 0;
}

int getIndexByName(Graph *graph, char *name){
	for(int i = 0; i < graph->size; i++){
		if (strcmp(name, graph->vertices[i].name) == 0)
			return i;
	}
	return -1;
}

int addEdge(Graph *graph, char *from, char *to, int grade){
	int fromI, toI;
	fromI = getIndexByName(graph, from);
	toI = getIndexByName(graph, to);
	
	if (fromI == -1 || toI == -1 || fromI == toI){
		printf("No such names or are they the same!\n");
		return 1;
	}
	
	for(int i = 0; i < graph->vertices[fromI].count; i++){
		if (graph->vertices[fromI].edges[i].from == fromI && graph->vertices[fromI].edges[i].to == toI){
			printf("Such a relationship already exist!\n");
			return 1;
		}
	}

	if (graph->vertices[fromI].count == 0) {
		graph->vertices[fromI].edges = calloc(1, sizeof(Edge));
		if (graph->vertices[fromI].edges == NULL)
			return 1;
	}
	else {
		graph->vertices[fromI].edges = realloc(graph->vertices[fromI].edges, (graph->vertices[fromI].count + 1) * sizeof(Edge));
		if (graph->vertices[fromI].edges == NULL)
			return 1;
	}
	graph->vertices[fromI].edges[graph->vertices[fromI].count].from = fromI;
	graph->vertices[fromI].edges[graph->vertices[fromI].count].to = toI;
	graph->vertices[fromI].edges[graph->vertices[fromI].count].grade = grade;
	graph->vertices[fromI].count++;

	return 0;
}

int deleteVertex(Graph *graph, char *name){
	int index = getIndexByName(graph, name);
	if (index == -1){
		printf("No such element!\n");
		return 1;
	}
	int last = graph->size - 1;
	for(int i = 0; i < graph->size; i++){
		if (i == index){
			free(graph->vertices[i].name);
			free(graph->vertices[i].edges);
			graph->vertices[i].count = 0;
			graph->size--;
			graph->vertices[i] = graph->vertices[graph->size];
			if (graph->size == 0) {
				free(graph->vertices);
				graph->vertices = NULL;
				break;
			}
			else
				graph->vertices = realloc(graph->vertices, graph->size * sizeof(Vertex));
		}
		for(int j = 0; j < graph->vertices[i].count; j++){
			if (graph->vertices[i].edges[j].to == last) {
				graph->vertices[i].edges[j].to = index;
				break;
			}
			if (graph->vertices[i].edges[j].from == last) {
				graph->vertices[i].edges[j].from = index;
			}
			if (graph->vertices[i].edges[j].to == index) {
				graph->vertices[i].count--;
				graph->vertices[i].edges[j] = graph->vertices[i].edges[graph->vertices[i].count];
				if (graph->vertices[i].count == 0){
					free(graph->vertices[i].edges);
					graph->vertices[i].edges = NULL;
				}
				else{
					graph->vertices[i].edges = realloc(graph->vertices[i].edges, graph->vertices[i].count * sizeof(Edge));
					j--;
				}
			}
		}
	}

	return 0;
}

int deleteEdge(Graph *graph, char *from, char *to){
	int fromI, toI, flag = 1;
	fromI = getIndexByName(graph, from);
	toI = getIndexByName(graph, to);
	if (fromI == -1 || toI == -1 || fromI == toI){
		printf("No such names or are they the same!\n");
		return 1;
	}

	for(int i = 0; i < graph->size; i++){
		for(int j = 0; j < graph->vertices[i].count; j++){
			if (graph->vertices[i].edges[j].from == fromI && graph->vertices[i].edges[j].to == toI){
				flag = 0;
				graph->vertices[i].count--;
				graph->vertices[i].edges[j] = graph->vertices[i].edges[graph->vertices[i].count];
				if (graph->vertices[i].count == 0){
					free(graph->vertices[i].edges);
					graph->vertices[i].edges = NULL;
				}
				else
					graph->vertices[i].edges = realloc(graph->vertices[i].edges, graph->vertices[i].count * sizeof(Edge));
				break;
			}
		}
		if (!flag)
			break;
	}

	return flag;
}

int changeInfoAboutVertex(Graph *graph, char *oldName, char *newName){
	int indexOld = getIndexByName(graph, oldName);
	int indexNew = getIndexByName(graph, newName);
	if (indexOld == -1 || indexNew != -1){
		printf("No such name or new name has already exist!\n");
		return 1;
	}
	free(graph->vertices[indexOld].name);
	graph->vertices[indexOld].name = newName;

	return 0;
}

int changeInfoAboutEdge(Graph *graph, char *from, char *oldTo, char *newTo, int grade){
	int fromI = getIndexByName(graph, from);
	int oldToI = getIndexByName(graph, oldTo);
	int newToI = getIndexByName(graph, newTo);
	if (fromI == -1 || oldToI == -1 || newToI == -1){
		printf("Some name does not exist or new name = old name!\n");
		return 1;
	}

	for(int i = 0; i < graph->vertices[fromI].count; i++){
		if (graph->vertices[fromI].edges[i].to == oldToI){
			graph->vertices[fromI].edges[i].to = newToI;
			graph->vertices[fromI].edges[i].grade = grade;
			break;
		}
	}

	return 0;
}

int printGraph(Graph *graph){
	if (graph->size == 0){
		printf("Graph is empty!\n");
		return 1;
	}
	for(int i = 0; i < graph->size; i++){
		printf("From \"%s\":\n", graph->vertices[i].name);
		for(int j = 0; j < graph->vertices[i].count; j++){
			printf("\t\"%s\" (%d)\n", graph->vertices[graph->vertices[i].edges[j].to].name, graph->vertices[i].edges[j].grade);
		}
	}
	return 0;
}

char** breadthFirstSearch(Graph *graph, char *name, int handshakes){
	int index = getIndexByName(graph, name);
	if (index == -1)
		return NULL;
	BFSstruct *bfsS = calloc(graph->size, sizeof(BFSstruct));
	for(int i = 0; i < graph->size; i++){
		bfsS[i].color = WHITE;
		bfsS[i].distance = 0;
	}
	bfsS[index].color = GREY;

	Queue *q = queue_new();
	queue_put(q, index);
	int currentIndex;
	while(queue_is_empty(q) == 0){
		queue_get(q, &currentIndex);
		for(int i = 0; i < graph->vertices[currentIndex].count; i++){
			if (bfsS[graph->vertices[currentIndex].edges[i].to].color == WHITE){
				bfsS[graph->vertices[currentIndex].edges[i].to].color = GREY;
				bfsS[graph->vertices[currentIndex].edges[i].to].distance = bfsS[graph->vertices[currentIndex].edges[i].from].distance + 1;
				queue_put(q, graph->vertices[currentIndex].edges[i].to);
			}
		}
		bfsS[currentIndex].color = BLACK;
	}

	queue_delete(q);

	char **names = calloc(graph->size, sizeof(char *));
	int j = 0;
	for(int i = 0; i < graph->size; i++){
		if (bfsS[i].distance > 0 && bfsS[i].distance <= handshakes){
			names[j] = strdup(graph->vertices[i].name);
			j++;
		}
	}
	if (j < graph->size)
		names[j] = NULL;

	free(bfsS);

	return names;
}

int dijkstra(Graph *graph, char *from, char *to){
	int fromI = getIndexByName(graph, from);
	int toI = getIndexByName(graph, to);
	if (fromI == -1 || toI == -1 || fromI == toI){
		printf("No such names or are they the same!\n");
		return 1;
	}

	// DijkstraS *dijkstraVertex = calloc(graph->size, sizeof(DijkstraS));
	// for(int i = 0; i < graph->size; i++){
	// 	dijkstraVertex[i].color = WHITE;
	// 	dijkstraVertex[i].distance = INT_MAX;
	// 	dijkstraVertex[i].prev = -1;
	// }
	// dijkstraVertex[from].distance = 0;

	int *distances = calloc(graph->size, sizeof(int));	// массив расстояний
	int *visited = calloc(graph->size, sizeof(int)); // массив посещенных вершин
	int *prev = calloc(graph->size, sizeof(int));
	for (int i = 0; i < graph->size; i++) {
		distances[i] = INT_MAX; // инициализация расстояний
		visited[i] = 0; // инициализация массива посещенных вершин
		prev[i] = -1;
	}
	distances[fromI] = 0; // расстояние до начальной вершины равно 0
	visited[fromI] = 1;
	int current = fromI;
	int min_distance, next_vertex;
	while (1) {
		min_distance = INT_MAX;
		for (int i = 0; i < graph->vertices[current].count; i++) { // обходим все соседние вершины
			Edge edge = graph->vertices[current].edges[i];
			if (edge.grade < 0)
				continue;
			if (distances[current] + edge.grade < distances[edge.to]) { // если можем пройти с меньшим расстоянием
				distances[edge.to] = distances[current] + edge.grade; // обновляем расстояние
				visited[edge.to] = 1;
				prev[edge.to] = current;
			}
		}
		visited[current] = 2;
		// выбираем следующую вершину с наименьшей оценкой
		for (int i = 0; i < graph->size; i++) { // проходим по всем вершинам
			if (visited[i] == 1 && distances[i] < min_distance) {
				min_distance = distances[i];
				next_vertex = i;
			}
		}
		if (min_distance == INT_MAX) {
			break; // все вершины пройдены
		}
		else {
			current = next_vertex;
			visited[current] = 1;
		}
	}
	// for(int i = 0; i < graph->size; i++)
	// 	printf("%d ", visited[i]);
	// printf("\n");
	// for(int i = 0; i < graph->size; i++)
	// 	printf("%d ", distances[i]);
	// printf("\n");
	// for(int i = 0; i < graph->size; i++)
	// 	printf("%d ", prev[i]);
	// printf("\n");
	if (distances[toI] == INT_MAX){
		free(visited);
		free(distances);
		free(prev);
		return 1;
	}

	int i = toI, j = 0;
	while(1){
		if (j == 0) {
			printf("\"%s\" ", graph->vertices[i].name);
			j++;
		}
		else
			printf("<- \"%s\" ", graph->vertices[i].name);
		i = prev[i];
		if (i == -1)
			break;
	}
	printf("(%d)\n", distances[toI]);

	free(visited);
	free(distances);
	free(prev);

	return 0;
}

void split(char *data, char **from, char **to, int *grade){
	char *istr;
	int i = 0;
	istr = strtok(data, " \n");
	while(istr != NULL){
		if (i % 3 == 0) {
			*from = strdup(istr);
		}
		else if (i % 3 == 1) {
			*to = strdup(istr);
		}
		else {
			*grade = atoi(istr);
		}
		istr = strtok(NULL, " \n");
		i++;
	}
	free(istr);
}

int importData(Graph **graph){
	if ((*graph)->size != 0)
		removeGraph(*graph);
	else
		free(*graph);

	FILE *file;
	char str[50];
	char *estr, *name;

	file = fopen("vertex.txt", "r");
	if (!file){
		printf("Can't open file!\n");
		return 1;
	}

	*graph = makeGraph();

	while(!feof(file)){
		estr = fgets(str, sizeof(str), file);
		if (estr == NULL)
			break;
		name = strdup(str);
		name[strlen(name) - 1] = '\0';
		addVertex(*graph, name);
	}
	free(estr);
	fclose(file);

	file = fopen("edge.txt", "r");
	if (!file){
		printf("Can't open file!\n");
		return 1;
	}

	char *from = NULL, *to = NULL, *data;
	int grade;

	while(!feof(file)){
		estr = fgets(str, sizeof(str), file);
		if (estr == NULL)
			break;
		data = strdup(str);
		split(data, &from, &to, &grade);
		free(data);
		addEdge(*graph, from, to, grade);
		free(from);
		free(to);
	}
	free(estr);
	fclose(file);

	return 0;
}
