#ifndef DIALOG_H
#define DIALOG_H

#include "RBTree.h"

int dAddNode(Tree **tree);

int dDeleteNode(Tree **tree);

int dFindNode(Tree **tree);

int dPrintTree(Tree **tree);

int dTreeTraversal(Tree **tree);

int dImport(Tree **tree);

int dExport(Tree **tree);

int dBenchmarkTest(Tree **tree);

#endif
