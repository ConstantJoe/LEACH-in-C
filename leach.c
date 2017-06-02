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

	printf("In leach 1\r\n");
	printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", clusterM.nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", clusterM.nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", clusterM.nodeA.node[0].dead);
        printf("\r\n");

	NodeArch nodeA = clusterM.nodeA;
	NetArch netA = clusterM.netA;

	printf("In leach 2\r\n");
	printf("Node 1 characteristics: %d\r\n", nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].dead);
        printf("\r\n");

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

	printf("In leach 3\r\n");
	printf("Node 1 characteristics: %d\r\n", nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].dead);
        printf("\r\n");

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

	printf("In leach 4\r\n");
	printf("Node 1 characteristics: %d\r\n", nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].dead);
        printf("\r\n");

	nodeA.numDead = deadCount;


	struct ClusterNodes *clusterN = malloc(sizeof *clusterN); 

	//find the cluster head
	int countCHs = 0;
	srand(time(NULL)); 


	for(int i=0; i<nodeA.numNode; i++)
	{
		if(!(nodeA.node[i].dead))
		{
			int temp_rand = rand(); 

			if(nodeA.node[i].G <= 0 && ((temp_rand % 100) <= (100 * prob(r, p))) && (nodeA.node[i].energy > 0))
			{
				printf("Cluster head added %d\r\n", i);
				countCHs++;
				printf("Node 1 characteristics 1: %c\r\n", nodeA.node[0].type);

				nodeA.node[i].type = 'C';
				printf("Node 1 characteristics 2: %c\r\n", nodeA.node[0].type);

				nodeA.node[i].G	= round(1/p)-1; //is this right?
				printf("Node 1 characteristics 3: %c\r\n", nodeA.node[0].type);

				printf("Node 1 characteristics add 1: %p\r\n", &nodeA.node[0].type);
				//printf("Node 1 characteristics add 2: %p\r\n", clusterN.cNodes[countCHs].no);

				clusterN->cNodes[countCHs].no = i;  //the problem is here.
				printf("Node 1 characteristics 4: %c\r\n", nodeA.node[0].type);

				printf("Node 1 characteristics add 1: %p\r\n", &nodeA.node[0].type);
				//printf("Node 1 characteristics add 2: %p\r\n", &clusterN.cNodes[countCHs].no);

				clusterN->cNodes[countCHs].locX = nodeA.node[i].x; 
				printf("Node 1 characteristics 5: %c\r\n", nodeA.node[0].type);

				clusterN->cNodes[countCHs].locY = nodeA.node[i].y;
				printf("Node 1 characteristics 6: %c\r\n", nodeA.node[0].type);


				clusterN->cNodes[countCHs].distance = sqrt(pow(nodeA.node[i].x - netA.sink.x, 2) + pow(nodeA.node[i].y - netA.sink.y, 2));
				printf("Node 1 characteristics 7: %c\r\n", nodeA.node[0].type);
			}
		}
	}

	printf("In leach 5\r\n");
	printf("Node 1 characteristics: %d\r\n", nodeA.node[0].x);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].y);
        printf("Node 1 characteristics: %c\r\n", nodeA.node[0].type);
        printf("Node 1 characteristics: %f\r\n", nodeA.node[0].energy);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].G);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].clusterHead);
        printf("Node 1 characteristics: %d\r\n", nodeA.node[0].dead);
        printf("\r\n");


	clusterN->countCHs = countCHs;

	clusterM.clusterN = *clusterN;
	clusterM.nodeA = nodeA;

	printf("In leach 6\r\n");
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