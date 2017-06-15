#include "newCluster.h"

double clusterOptimum(NetArch* netA, NodeArch* nodeA, double dBS)
{
	int n = nodeA->numNode - nodeA->numDead;
	double m = sqrt(netA->yard.height * netA->yard.width);

	float x = netA->energy.freespace / netA->energy.multipath;

	double kopt = sqrt(n) / sqrt(2*M_PI) * sqrt(netA->energy.freespace / netA->energy.multipath) * m / pow(dBS,2);
	kopt = round(kopt);
	return kopt;
}

ClusterModel* newCluster(NetArch* netA, NodeArch* nodeA)
{
	struct ClusterModel *clusterM = malloc(sizeof *clusterM); 
	clusterM->netA = *netA;
	clusterM->nodeA = *nodeA;

	return clusterM;
}

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