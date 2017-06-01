#include "clusterModel.h"

ClusterModel newCluster(NetArch netA, NodeArch nodeA, int roundNo, int p_numCluster)
{
	struct ClusterModel clusterM;

	clusterM.netA = netA;
	clusterM.nodeA = nodeA;

	if(p_numCluster == 0)
	{
		float dBS = sqrt((netA.sink.x - netA.yard.length)^2 + (netA.sink.y - netA.yard.width)^2);
		clusterM.numCluster = clusterOptimum(netA, nodeA, dBS);
		clusterM.p = 1 / numCluster;	
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