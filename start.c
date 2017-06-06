#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "netArchitecture.h"
#include "nodeArchitecture.h"
#include "roundArchitecture.h"
#include "clusterModel.h"
#include "leach.h"
#include "dissEnergy.h"
#include "newCluster.h"

#define NUMNODES 100
#define P 	0.1

//TODO: energy of nodes continues to drop even after death?
//      Once working, remove unnecessary libs (e.g. stdio)
//      Better documentation needed.   
//      Add clean to Makefule

int main() 
{  
    printf("Testing 1\r\n");
  
	struct NetArch* netA  	 = newNetwork(100, 100, 50, 175);
	struct NodeArch* nodeA 	 = newNodes(netA, NUMNODES);
	struct RoundArch* roundA  = newRound(0,0,0);

    printf("Testing 2\r\n");

	for(int i=0; i<roundA->numRound; i++)
	{
        printf("Node 1 characteristics: %d\r\n", nodeA->node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA->node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA->node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA->node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA->node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA->node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA->node[0].dead);

		struct ClusterModel* clusterM = newCluster(netA, nodeA, i, P); 	

        clusterM  = dissEnergyCH(clusterM, roundA);
    	
        clusterM  = dissEnergyNonCH(clusterM, roundA);
    	
        nodeA     = &clusterM->nodeA; 
    
        printf("Round %d \r\n", i);
        printf("NumNodes %d \r\n", nodeA->numNode);
        printf("NumDead %d \r\n\r\n", nodeA->numDead);

    	if(nodeA->numDead == nodeA->numNode)
    	{
            printf("All are dead \r\n");
            printf(" %d  \r\n", nodeA->numDead);
            printf(" %d  \r\n", nodeA->numNode);
        	break;
    	}
	}
}