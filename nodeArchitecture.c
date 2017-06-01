#include "nodeArchitecture.h"


struct NodeArch newNodes(NetArch netA, int numNodes)
{
	srand(time(NULL)); 

	if(numNodes == 0)
	{
		numNodes = 100;
	}	

	NodeArch nodeA;
	//nodeA = malloc(sizeof(struct NodeArch)); 

	for(int i=0;i<numNodes;i++)
	{
		int r = rand(); 

		//need to allocate space for each of the nodes
		nodeA.node[i].x = r * netA.yard.width; 
		nodeA.node[i].y = r * netA.yard.height;	// cant access inner node properties this way
		nodeA.node[i].G = 0; 
		nodeA.node[i].type = 'N';
		nodeA.node[i].energy = netA.energy.init;
		nodeA.node[i].clusterHead = -1;
		nodeA.node[i].dead = 0;
	}

	nodeA.numNode = numNodes;
	nodeA.numDead = 0;

	return nodeA;
}