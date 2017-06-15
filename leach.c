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

struct ClusterModel* leach(ClusterModel* clusterM, int roundNo)
{
	int r = roundNo;
	float p = clusterM->p;
	int n = clusterM->nodeA.numNode;

	if(clusterM->numCluster != 0)
	{
		if(r % (int) clusterM->numCluster == 0)
		{	
			for(int i=0;i<n;i++)
			{
				clusterM->nodeA.node[i].G = 0;
			}
		}	
	}
	
	int deadCount = 0;
	for(int i=0; i<clusterM->nodeA.numNode; i++)
	{
		if(!(clusterM->nodeA.node[i].dead))
		{
			if(clusterM->nodeA.node[i].energy <= 0)
			{
				clusterM->nodeA.node[i].type = 'D';
            	clusterM->nodeA.node[i].dead = 1;
            	deadCount++;
			}
			else
			{
				clusterM->nodeA.node[i].type = 'N';
			}	
		}
		else
		{
			deadCount++;
		}
	}

	clusterM->nodeA.numDead = deadCount;

	//find the cluster head

	//Change this to reflect the paper
	int countCHs = 0;
	clusterM->clusterN.countCHs = 0;
	srand(time(NULL)); 

	if(clusterM->numCluster == 0){
		clusterM->numCluster = 1;

		for(int i=0; i<clusterM->nodeA.numNode; i++)
		{
			if(!(clusterM->nodeA.node[i].dead))
			{
				clusterM->nodeA.node[i].type = 'C';

				clusterM->nodeA.node[i].G	= round(1/p)-1;

				clusterM->clusterN.cNodes[countCHs].no = i; 

				clusterM->clusterN.cNodes[countCHs].locX = clusterM->nodeA.node[i].x; 

				clusterM->clusterN.cNodes[countCHs].locY = clusterM->nodeA.node[i].y;

				clusterM->clusterN.cNodes[countCHs].distance = sqrt(pow(clusterM->nodeA.node[i].x - clusterM->netA.sink.x, 2) + pow(clusterM->nodeA.node[i].y - clusterM->netA.sink.y, 2));

				countCHs++;

				if(countCHs == clusterM->numCluster){
					break;
				}
			}
		}
	} else{
		int stop = 1;
		while(countCHs < clusterM->numCluster && stop){
			for(int i=0; i<clusterM->nodeA.numNode; i++)
			{
				if(!(clusterM->nodeA.node[i].dead))
				{
					int temp_rand = rand(); 

			

					//if(clusterM->nodeA.node[i].G <= 0 && ((temp_rand % 100) <= (100 * prob(n-deadCount, p))) && (clusterM->nodeA.node[i].energy > 0))
					//if(clusterM->nodeA.node[i].G <= 0 && ((temp_rand % 100) <= (100 *  p)) && (clusterM->nodeA.node[i].energy > 0))
					if(clusterM->nodeA.node[i].G <= 0 && ((temp_rand % (clusterM->nodeA.numNode - clusterM->nodeA.numDead)) <= clusterM->numCluster) && (clusterM->nodeA.node[i].energy > 0) && clusterM->nodeA.node[i].type != 'C')
					{
						clusterM->nodeA.node[i].type = 'C';

						clusterM->nodeA.node[i].G	= round(1/p)-1;

						clusterM->clusterN.cNodes[countCHs].no = i; 

						clusterM->clusterN.cNodes[countCHs].locX = clusterM->nodeA.node[i].x; 

						clusterM->clusterN.cNodes[countCHs].locY = clusterM->nodeA.node[i].y;

						clusterM->clusterN.cNodes[countCHs].distance = sqrt(pow(clusterM->nodeA.node[i].x - clusterM->netA.sink.x, 2) + pow(clusterM->nodeA.node[i].y - clusterM->netA.sink.y, 2));

						countCHs++;

						if(countCHs == clusterM->numCluster){
							stop = 0;
							break;
						}
					}
				}
			}
		}
	}

	clusterM->clusterN.countCHs = countCHs;

	return clusterM;
}