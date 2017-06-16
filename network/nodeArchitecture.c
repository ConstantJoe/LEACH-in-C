/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "nodeArchitecture.h"

/*
 *	Generates numNodes number of nodes in random locations across the defined 2D environment.
 */
struct NodeArch* newNodes(NetArch* netA, int numNodes)
{
	srand(time(NULL)); 

	if(numNodes == 0)
	{
		numNodes = 100;
	}	

	struct NodeArch *nodeA = malloc(sizeof *nodeA); 

	for(int i=0;i<numNodes;i++)
	{
		nodeA->node[i].x = rand() % netA->yard.width; 	
		nodeA->node[i].y = rand() % netA->yard.height;
		nodeA->node[i].G = 0; 
		nodeA->node[i].type = 'N';
		nodeA->node[i].energy = netA->energy.init;
		nodeA->node[i].clusterHead = -1;
		nodeA->node[i].dead = 0;
	}

	nodeA->numNode = numNodes;
	nodeA->numDead = 0;

	return nodeA;
}