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
#define P 	0

//TODO: Behaviour when down to last two nodes.
//      Cleanup
//      Once working, remove unnecessary libs (e.g. stdio)
//      Better documentation needed.   
//      Add clean to Makefile
//      Visualisation / data output
//      LEACH-C version

int main() 
{  
	struct NetArch* netA  	 = newNetwork(100, 100, 50, 175);
	struct NodeArch* nodeA 	 = newNodes(netA, NUMNODES);
	struct RoundArch* roundA  = newRound(0,0,0);
    struct ClusterModel* clusterM = newCluster(netA, nodeA);  

	for(int i=0; i<roundA->numRound; i++)
	{		
        clusterM = clusterRun(clusterM, i, P);

        if(nodeA->numDead == nodeA->numNode)
        {
            printf("All are dead \r\n");
            printf(" %d  \r\n", nodeA->numDead);
            printf(" %d  \r\n", nodeA->numNode);
            break;
        }

        clusterM  = dissEnergyCH(clusterM, roundA);

        clusterM  = dissEnergyNonCH(clusterM, roundA);

        nodeA     = &clusterM->nodeA; 
        printf("Round %d \r\n", i);
        printf("NumNodes %d \r\n", nodeA->numNode);
        printf("NumDead %d \r\n\r\n", nodeA->numDead);

    	
	}
}