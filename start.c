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
#define P 	0

//TODO: Behaviour when down to last two nodes.
//      Use of .G, which stops the same nodes being chose as CHs over and over
//      Once working, remove unnecessary libs (e.g. stdio)
//      Better documentation needed.   
//      Add clean to Makefile
//      Visualisation / data output

int main() 
{  
    printf("Testing 1\r\n");
  
	struct NetArch* netA  	 = newNetwork(100, 100, 50, 175);
	struct NodeArch* nodeA 	 = newNodes(netA, NUMNODES);
	struct RoundArch* roundA  = newRound(0,0,0);
    struct ClusterModel* clusterM = newCluster(netA, nodeA);  

    printf("Testing 2\r\n");

	for(int i=0; i<roundA->numRound; i++)
	{
        if(nodeA->numNode - nodeA->numDead < 5){
            for(int i=0; i<clusterM->nodeA.numNode; i++){
                if(clusterM->nodeA.node[i].dead == 0){
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].x);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].y);
                    printf("Node %d characteristics: %c\r\n", i, nodeA->node[i].type);
                    printf("Node %d characteristics: energy 1 %f\r\n", i, nodeA->node[i].energy);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].G);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].clusterHead);
                    printf("Node %d characteristics: %d\r\n\r\n", i, nodeA->node[i].dead);
                }
            }
        }
        else{
            printf("Node 1 characteristics: %d\r\n", nodeA->node[0].x);
            printf("Node 1 characteristics: %d\r\n", nodeA->node[0].y);
            printf("Node 1 characteristics: %c\r\n", nodeA->node[0].type);
            printf("Node 1 characteristics: energy 1 %f\r\n", nodeA->node[0].energy);
            printf("Node 1 characteristics: %d\r\n", nodeA->node[0].G);
            printf("Node 1 characteristics: %d\r\n", nodeA->node[0].clusterHead);
            printf("Node 1 characteristics: %d\r\n", nodeA->node[0].dead);
        }
        

		
        clusterM = clusterRun(clusterM, i, P);
       // clusterM = leach(clusterM, roundNo);

        int n = clusterM->clusterN.countCHs;
         printf("CHs: %d\r\n", n);
        /*for(int i=0;i<n;i++)
        {
             printf("s node id 3: %d\r\n", clusterM->clusterN.cNodes[i].no);
        }*/

        printf("Node 1 characteristics: energy 2 %f\r\n", clusterM->nodeA.node[0].energy);


        clusterM  = dissEnergyCH(clusterM, roundA);
    	
        printf("Node 1 characteristics: energy 3 %f\r\n", clusterM->nodeA.node[0].energy);

        clusterM  = dissEnergyNonCH(clusterM, roundA);
    	
        printf("Node 1 characteristics: energy 4 %f\r\n", clusterM->nodeA.node[0].energy);

        nodeA     = &clusterM->nodeA; 
    
        printf("Node 1 characteristics: energy 5 %f\r\n", nodeA->node[0].energy);

        printf("Round %d \r\n", i);
        printf("NumNodes %d \r\n", nodeA->numNode);
        printf("NumDead %d \r\n\r\n", nodeA->numDead);

    	if(nodeA->numDead == nodeA->numNode - 2)
    	{
            printf("All are dead \r\n");
            printf(" %d  \r\n", nodeA->numDead);
            printf(" %d  \r\n", nodeA->numNode);

            for(int i=0; i<clusterM->nodeA.numNode; i++){
                if(clusterM->nodeA.node[i].dead == 0){
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].x);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].y);
                    printf("Node %d characteristics: %c\r\n", i, nodeA->node[i].type);
                    printf("Node %d characteristics: energy %f\r\n", i, nodeA->node[i].energy);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].G);
                    printf("Node %d characteristics: %d\r\n", i, nodeA->node[i].clusterHead);
                    printf("Node %d characteristics: %d\r\n\r\n", i, nodeA->node[i].dead);
                }
            }
        	break;
    	}
	}
}