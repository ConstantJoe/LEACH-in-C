#include "netArchitecture.h"
#include "nodeArchitecture.h"
#include <math.h>

#ifndef CLUSTERMODEL_H
#define CLUSTERMODEL_H

#define MAX_CHS
//These should all be arrays?

typedef struct ClusterNode{
	int no; //index of the node in the nodeArchitecture
	int locX;
	int locY;
	double distance; //distance from sink
} ClusterNode;

typedef struct ClusterNodes{
	int countCHs;
	ClusterNode cNodes[MAX_CHS];
} ClusterNodes; 

typedef struct ClusterModel{
	NetArch netA;
	NodeArch nodeA;
	int numCluster;
	float p;
	ClusterNodes clusterN;
} ClusterModel;

#endif /* CLUSTERMODEL_H */



