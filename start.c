/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./network/netArchitecture.h"
#include "./network/nodeArchitecture.h"
#include "./network/roundArchitecture.h"
#include "./network/clusterModel.h"
#include "./leach_algorithm/leach.h"
#include "./energy/dissEnergy.h"
#include "./network/newCluster.h"

#define P 	0


int main(int argc, char *argv[] ) 
{
    //default values for cmd line arguments
    int envLength = 100; 
    int envWidth = 100;
    int sinkX = 50;
    int sinkY = 50;
    int numNodes = 100;
    int maxRounds = 9999; 
    int packetLength = 6400;
    int ctrPacketLength = 6400;

    int i;
    //cmd parameter format checker.
    //argv should be in format [filename str int str int str int...]
    int pass = 1;
    for(i=1; i<argc; i++){
        if(i%2 == 1){
            if(!(!strcmp(argv[i], "envLength") || !strcmp(argv[i], "envWidth") || !strcmp(argv[i], "sinkX") || !strcmp(argv[i], "sinkY") | 
               !strcmp(argv[i], "numNodes") || !strcmp(argv[i], "maxRounds") || !strcmp(argv[i], "packetLength") || !strcmp(argv[i], "ctrPacketLength"))){
                printf("ERROR: command line arguments not in correct format. Do not recognise: %s\r\n", argv[i]);
                pass = 0;
                break;
            }
        } else{
            int j;
            char* x = argv[i];
            for(j=0; j< strlen(x); j++){
                if(!isdigit(x[j])){
                    printf("ERROR: command line arguments not in correct format. Do not recognise: %s\r\n", argv[i]);
                    pass = 0;
                    break;
                }
            }
        }
    }
    if(!pass){
        return(0);
    }

    
    for(i=1; i<argc; i++){
        if(strcmp(argv[i], "envLength") == 0){
            envLength = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "envWidth") == 0){
            envWidth = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "sinkX") == 0){
            sinkX = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "sinkY") == 0){
            sinkY = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "numNodes") == 0){
            numNodes = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "maxRounds") == 0){
            maxRounds = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "packetLength") == 0){
            packetLength = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i], "ctrPacketLength") == 0){
            ctrPacketLength = atoi(argv[i+1]);
        }
    }  
	struct NetArch* netA  	 = newNetwork(envLength, envWidth, sinkX, sinkY);
	struct NodeArch* nodeA 	 = newNodes(netA, numNodes);
	struct RoundArch* roundA  = newRound(maxRounds, packetLength, ctrPacketLength);
    struct ClusterModel* clusterM = newClusterModel(netA, nodeA);  

	for(i=0; i<roundA->numRound; i++)
	{		
        clusterM = clusterRun(clusterM, i, P);

        if(nodeA->numDead == nodeA->numNode)
        {
            printf("All are dead \r\n");
            printf(" %d  \r\n", nodeA->numDead);
            printf(" %d  \r\n", nodeA->numNode);
            break;
        }
        
        clusterM  = dissEnergyCH(clusterM, roundA);
        clusterM  = dissEnergyNonCH(clusterM, roundA);

        nodeA     = &clusterM->nodeA; 
        printf("Round %d \r\n", i);
        printf("NumNodes %d \r\n", nodeA->numNode);
        printf("NumDead %d \r\n\r\n", nodeA->numDead);

    	
	}

    return(0);
}
