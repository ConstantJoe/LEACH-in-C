#include "newCluster.h"

int clusterOptimum(NetArch netA, NodeArch nodeA, float dBS)
{
	int n = nodeA.numNode;
	int m = sqrt(netA.yard.height * netA.yard.width);
	float kopt = sqrt(n) / sqrt(2*M_PI) * sqrt(netA.energy.freespace / netA.energy.multipath) * m / pow(dBS,2);
	kopt = round(kopt);
	return (int) kopt;
}

ClusterModel newCluster(NetArch netA, NodeArch nodeA, int roundNo, int p_numCluster)
{
	struct ClusterModel clusterM;

	clusterM.netA = netA;
	clusterM.nodeA = nodeA;

	if(p_numCluster == 0)
	{
		float dBS = sqrt(pow(netA.sink.x - netA.yard.height, 2) + pow(netA.sink.y - netA.yard.width, 2));
		clusterM.numCluster = clusterOptimum(netA, nodeA, dBS);
		clusterM.p = 1 / p_numCluster;	
	}
	else
	{
		if(p_numCluster < 1)
		{
			clusterM.p = p_numCluster;
			clusterM.numCluster = 1 / p_numCluster; 
		}
		else
		{
			clusterM.numCluster = p_numCluster;
			clusterM.p = 1 / p_numCluster;
		}
	}
	
	clusterM = leach(clusterM, roundNo);

	return clusterM;
}