/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "netArchitecture.h"
#include "nodeArchitecture.h"
#include <math.h>

#ifndef CLUSTERMODEL_H
#define CLUSTERMODEL_H

#define MAX_CHS

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
	float numCluster;
	float p;
	ClusterNodes clusterN;
} ClusterModel;

#endif /* CLUSTERMODEL_H */



