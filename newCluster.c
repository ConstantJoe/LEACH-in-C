/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "newCluster.h"

/*
 *	Calculates the optimal number of clusters based on the area size, number of nodes, and communication energy models.
 *	See "An Application-Specific Protocol Architecture for Wireless Microsensor Networks" by Heinzelman et. al. for a 
 *	derivation of the formula.
 */
double clusterOptimum(NetArch* netA, NodeArch* nodeA, double dBS)
{
	int n = nodeA->numNode - nodeA->numDead;
	double m = sqrt(netA->yard.height * netA->yard.width);

	float x = netA->energy.freespace / netA->energy.multipath;

	double kopt = sqrt(n) / sqrt(2*M_PI) * sqrt(netA->energy.freespace / netA->energy.multipath) * m / pow(dBS,2);
	kopt = round(kopt);
	return kopt;
}

/**
*	Creates a "blank" cluster model to use in this round of operation, populated with just information on the environment and 
*	individual node locations and energies. Creation of clusters from this is handled in the clusterRun function.
**/
ClusterModel* newClusterModel(NetArch* netA, NodeArch* nodeA)
{
	struct ClusterModel *clusterM = malloc(sizeof *clusterM); 
	clusterM->netA = *netA;
	clusterM->nodeA = *nodeA;

	return clusterM;
}

/**
*	Calculates the optimal number of nodes, then calls the leach algorithm to generate clusters. Leach algorithm is defined separately
*	to enable this method to be easily modified to handle a different clustering algorithm.  
**/

ClusterModel* clusterRun(ClusterModel* clusterM, int roundNo, float p_numCluster)
{
	if(p_numCluster == 0)
	{
		double dBS = sqrt(pow(clusterM->netA.sink.x - clusterM->netA.yard.height, 2) + pow(clusterM->netA.sink.y - clusterM->netA.yard.width, 2));
		clusterM->numCluster = clusterOptimum(&clusterM->netA, &clusterM->nodeA, dBS);

		if(clusterM->numCluster == 0){
			clusterM->p = 1; //when there's only 1 node left optimal # of CHs is 0 -> ensure only node is set as the CH
		} else{
			clusterM->p = 1 / clusterM->numCluster;	
		}	
	}
	else
	{
		if(p_numCluster < 1)
		{
			clusterM->p = p_numCluster;
			clusterM->numCluster = 1 / p_numCluster; 
		}
		else
		{
			clusterM->numCluster = p_numCluster;
			clusterM->p = 1 / p_numCluster;
		}
	}

	clusterM = leach(clusterM, roundNo);

	return clusterM;
}