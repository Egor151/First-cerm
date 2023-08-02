#ifndef GRAPH_H
#define GRAPH_H

enum Color {
	WHITE,
	GREY,
	BLACK
};

typedef struct Edge {
	int from;
	int to;
	int grade;
} Edge;

typedef struct Vertex {
	char *name;
	int count;
	Edge *edges;
} Vertex;

typedef struct Graph {
	int size;
	Vertex *vertices;
} Graph;

Graph *makeGraph();

void removeGraph(Graph *graph);

int addVertex(Graph *graph, char *name);

int addEdge(Graph *graph, char *from, char *to, int grade);

int deleteVertex(Graph *graph, char *name);

int deleteEdge(Graph *graph, char *from, char *to);

int changeInfoAboutVertex(Graph *graph, char *oldName, char *newName);

int changeInfoAboutEdge(Graph *graph, char *from, char *oldTo, char *newTo, int grade);

int printGraph(Graph *graph);

typedef struct BFSstruct {
	enum Color color;
	int distance;
} BFSstruct;

char** breadthFirstSearch(Graph *graph, char *name, int handshakes);

typedef struct DijkstraS{
	enum Color color;
	int index;
	int distance;
	int prev;
} DijkstraS;

int dijkstra(Graph *graph, char *from, char *to);

int importData(Graph **graph);

#endif
