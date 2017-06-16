/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "./network/netArchitecture.h"
#include "./network/nodeArchitecture.h"
#include "./network/roundArchitecture.h"
#include "./network/clusterModel.h"
#include "./leach_algorithm/leach.h"
#include "./energy/dissEnergy.h"
#include "./network/newCluster.h"

#define NUMNODES 100
#define P 	0

int main() 
{  
	struct NetArch* netA  	 = newNetwork(100, 100, 50, 175);
	struct NodeArch* nodeA 	 = newNodes(netA, NUMNODES);
	struct RoundArch* roundA  = newRound(0,0,0);
    struct ClusterModel* clusterM = newClusterModel(netA, nodeA);  

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
