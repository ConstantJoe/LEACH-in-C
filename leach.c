#include "leach.h"

float prob(int roundNo, float p)
{
	if(p == 0)
	{
		p = 0.1;
	}

	float P = p / (1-p * (roundNo % ( (int) round(1/p))) );

	return P;
}

struct ClusterModel leach(ClusterModel clusterM, int roundNo)
{
	NodeArch nodeA = clusterM.nodeA;
	NetArch netA = clusterM.netA;

	int r = roundNo;
	float p = clusterM.p;
	int n = nodeA.numNode;

	if(r % clusterM.numCluster == 0)
	{
		for(int i=0;i<n;i++)
		{
			nodeA.node[i].G = 0;
		}
	}

	int deadCount = 0;
	for(int i=0; i<nodeA.numNode; i++)
	{
		if(!(nodeA.node[i].dead))
		{
			if(nodeA.node[i].energy <= 0)
			{
				nodeA.node[i].type = 'D';
            	nodeA.node[i].dead = 1;
            	deadCount++;
			}
			else
			{
				nodeA.node[i].type = 'N';
			}	
		}
		else
		{
			deadCount++;
		}
	}


	nodeA.numDead = deadCount;


	struct ClusterNodes clusterN;

	//find the cluster head
	int countCHs = 0;
	srand(time(NULL)); 

	for(int i=0; i<nodeA.numNode; i++)
	{
		if(!(nodeA.node[i].dead))
		{
			int temp_rand = rand(); 

			if(nodeA.node[i].G <= 0 && (temp_rand <= prob(r, p)) && (nodeA.node[i].energy > 0))
			{
				countCHs++;

				nodeA.node[i].type = 'C';
				nodeA.node[i].G	= round(1/p)-1; //is this right?
				clusterN.cNodes[countCHs].no = i; 
		
				clusterN.cNodes[countCHs].locX = nodeA.node[i].x; 
				clusterN.cNodes[countCHs].locY = nodeA.node[i].y;

				clusterN.cNodes[countCHs].distance = sqrt((nodeA.node[i].x - netA.sink.x)^2 + (nodeA.node[i].y - netA.sink.y)^2);
			}
		}
	}
	clusterN.countCHs = countCHs;

	clusterM.clusterN = clusterN;
	clusterM.nodeA = nodeA;
	return clusterM;
}