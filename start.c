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

int main() 
{  
	struct NetArch netA  	 = newNetwork(100, 100, 50, 175);
	struct NodeArch nodeA 	 = newNodes(netA, NUMNODES);
	struct RoundArch roundA  = newRound(0,0,0);

	for(int i=0; i<roundA.numRound; i++)
	{
		struct ClusterModel clusterM = newCluster(netA, nodeA, i, P);
    	clusterM  = dissEnergyCH(clusterM, roundA);
    	clusterM  = dissEnergyNonCH(clusterM, roundA);
    	nodeA     = clusterM.nodeA; // new node architecture after select CHs
    
    	//par = plotResults(clusterModel, r, par);
    	if(nodeA.numDead == nodeA.numNode)
    	{
        	break;
    	}
	}
}