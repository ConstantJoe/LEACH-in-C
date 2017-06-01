#include "netArchitecture.h"
#include <time.h>
#include <stdlib.h>

#ifndef NODEARCHITECTURE_H
#define NODEARCHITECTURE_H

#define MAX_NODES 300

typedef struct Node {
	int x;
	int y;
	char type;
	int G;
	long energy;
	int clusterHead;
	int dead;
} Node;

typedef struct NodeArch {
	int numNode;
	int numDead;
	Node node[MAX_NODES];
} NodeArch;

NodeArch newNodes(NetArch netA, int numNodes);

#endif /* NODEARCHITECTURE_H */

