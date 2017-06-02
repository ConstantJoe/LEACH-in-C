#include "newCluster.h"

int clusterOptimum(NetArch netA, NodeArch nodeA, double dBS)
{
	int n = nodeA.numNode;
	double m = sqrt(netA.yard.height * netA.yard.width);

	float x = netA.energy.freespace / netA.energy.multipath;

	double kopt = sqrt(n) / sqrt(2*M_PI) * sqrt(netA.energy.freespace / netA.energy.multipath) * m / pow(dBS,2);
	kopt = round(kopt);
	return (int) kopt;
}

ClusterModel newCluster(NetArch netA, NodeArch nodeA, int roundNo, int p_numCluster)
{
	printf("In new cluster\r\n");
	printf("Node 1 characteristics: %d\r\n", nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].dead);
        printf("\r\n");

	//can't do it like this. Should use pointer to the struct instead.
	struct ClusterModel clusterM;
	clusterM.netA = netA;
	clusterM.nodeA = nodeA;

	printf("In new cluster 2\r\n");
	printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", clusterM.nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", clusterM.nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].dead);
        printf("\r\n");

	if(p_numCluster == 0)
	{
		double dBS = sqrt(pow(netA.sink.x - netA.yard.height, 2) + pow(netA.sink.y - netA.yard.width, 2));
		clusterM.numCluster = clusterOptimum(netA, nodeA, dBS);
		clusterM.p = 1 / clusterM.numCluster;	
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
	
	printf("In new cluster 3\r\n");
	printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", clusterM.nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", clusterM.nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].dead);
        printf("\r\n");

	clusterM = leach(clusterM, roundNo);

	printf("In new cluster 4\r\n");
	printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", clusterM.nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", clusterM.nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].dead);
        printf("\r\n");

	return clusterM;
}