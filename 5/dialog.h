#ifndef DIALOG_H
#define DIALOG_H

#include "graph.h"

int getInt(int *digit);

int dAddVertex(Graph **graph);

int dAddEdge(Graph **graph);

int dDeleteVertex(Graph **graph);

int dDeleteEdge(Graph **graph);

int dChangeInfoAboutVertex(Graph **graph);

int dChangeInfoAboutEdge(Graph **graph);

int dPrintGraph(Graph **graph);

int dBreadthFirstSearch(Graph **graph);

int dDijkstra(Graph **graph);

int dImport(Graph **graph);

#endif
