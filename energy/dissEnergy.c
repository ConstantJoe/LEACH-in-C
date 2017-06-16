/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "dissEnergy.h"

/*
 *  Calculate energy lost by each CH during the round. 
 */
ClusterModel* dissEnergyCH(ClusterModel* clusterM, RoundArch* roundA)
{
    double d0 = sqrt(clusterM->netA.energy.freespace / clusterM->netA.energy.multipath);

    int n = clusterM->clusterN.countCHs;

    float ETX = clusterM->netA.energy.transfer;
    float ERX = clusterM->netA.energy.receive;
    float EDA = clusterM->netA.energy.aggr;
    float Emp = clusterM->netA.energy.multipath;
    float Efs = clusterM->netA.energy.freespace;
    int packetLength = roundA->packetLength;
    int ctrPacketLength = roundA->ctrPacketLength;

    for(int i=0;i<n;i++)
    {
        int chNo = clusterM->clusterN.cNodes[i].no;
        double distance = clusterM->clusterN.cNodes[i].distance;

        if(distance >= d0)
        {
            clusterM->nodeA.node[chNo].energy -= ((ETX+EDA) * packetLength + Emp * packetLength * pow(distance, 4));
        }
        else
        {
            clusterM->nodeA.node[chNo].energy -= ((ETX+EDA) * packetLength + Efs * packetLength * pow(distance, 2));
        }
        clusterM->nodeA.node[chNo].energy -= ctrPacketLength * ERX * round(clusterM->nodeA.numNode / clusterM->numCluster);
    }

    return clusterM;
}

/*
 *  Calculate energy lost by each non-CH during the round. 
 */
ClusterModel* dissEnergyNonCH(ClusterModel* clusterM, RoundArch* roundA)
{    
    double d0 = sqrt(clusterM->netA.energy.freespace / clusterM->netA.energy.multipath);

    float ETX = clusterM->netA.energy.transfer;
    float ERX = clusterM->netA.energy.receive;
    float EDA = clusterM->netA.energy.aggr;
    float Emp = clusterM->netA.energy.multipath;
    float Efs = clusterM->netA.energy.freespace;
    int packetLength = roundA->packetLength;
    int ctrPacketLength = roundA->ctrPacketLength;

    for(int i=0; i<clusterM->nodeA.numNode; i++)
    {
        if(clusterM->nodeA.node[i].type == 'N' && clusterM->nodeA.node[i].dead == 0 && clusterM->nodeA.node[i].energy > 0)
        {
            int locNodeX = clusterM->nodeA.node[i].x;
            int locNodeY = clusterM->nodeA.node[i].y;
            int countCH = clusterM->clusterN.countCHs;

            //get the shortest distance to a cluster head
            int loc = 0;
            double minDis = 1000000;
            
            for(int j=0;j<countCH;j++)
            {
                double dist = sqrt( pow(locNodeX - clusterM->clusterN.cNodes[j].locX, 2) + pow(locNodeY - clusterM->clusterN.cNodes[j].locY, 2));
 
                if(dist < minDis)
                {
                    minDis = dist;
                    loc = j; 
                }
            }


            
            int minDisCH =  clusterM->clusterN.cNodes[loc].no;

            if (minDis > d0)
            {
                clusterM->nodeA.node[i].energy -= ctrPacketLength * ETX + Emp * packetLength * (pow(minDis, 4));
            }
            else
            {
                clusterM->nodeA.node[i].energy -= ctrPacketLength * ETX + Efs * packetLength * (pow(minDis, 2));
            }

            if(minDis > 0)
            {
                clusterM->nodeA.node[minDisCH].energy -= ((ERX + EDA) * packetLength);
            }     
        }
    }
    return clusterM;    
}
