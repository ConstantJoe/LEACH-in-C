#include "dissEnergy.h"

ClusterModel dissEnergyCH(ClusterModel clusterM, RoundArch roundA)
{

    NodeArch nodeA = clusterM.nodeA;
    NetArch netA  = clusterM.netA;
    ClusterNodes clusterN = clusterM.clusterN;

    float d0 = sqrt(netA.energy.freespace / netA.energy.multipath);

    /*if (clusterN.countCHs == 0)
    {
        return NULL;
    }*/

    int n = clusterN.countCHs;

    float ETX = netA.energy.transfer;
    float ERX = netA.energy.receive;
    float EDA = netA.energy.aggr;
    float Emp = netA.energy.multipath;
    float Efs = netA.energy.freespace;
    int packetLength = roundA.packetLength;
    int ctrPacketLength = roundA.ctrPacketLength;

    for(int i=0;i<n;i++)
    {
        int chNo = clusterN.cNodes[i].no;
        float distance = clusterN.cNodes[i].distance;
        float energy = nodeA.node[chNo].energy;

        if(distance >= d0)
        {
            nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Emp * packetLength * pow(distance, 2));
        }
        else
        {
            nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Efs * packetLength * pow(distance, 2));
        }
        nodeA.node[chNo].energy = nodeA.node[chNo].energy - ctrPacketLength * ERX * round(nodeA.numNode / clusterM.numCluster);
    }

    clusterM.nodeA = nodeA;

    return clusterM;
}

ClusterModel dissEnergyNonCH(ClusterModel clusterM, RoundArch roundA)
{
    NodeArch nodeA = clusterM.nodeA;
    NetArch netA  = clusterM.netA;
    ClusterNodes clusterN = clusterM.clusterN;

    /*if (clusterN.countCHs == 0)
    {
        return NULL;
    }*/

    float d0 = sqrt(netA.energy.freespace / netA.energy.multipath);

    float ETX = netA.energy.transfer;
    float ERX = netA.energy.receive;
    float EDA = netA.energy.aggr;
    float Emp = netA.energy.multipath;
    float Efs = netA.energy.freespace;
    int packetLength = roundA.packetLength;
    int ctrPacketLength = roundA.ctrPacketLength;

    for(int i=0; i<nodeA.numNode; i++)
    {
        if(nodeA.node[i].type == 'N' && nodeA.node[i].dead == 0 && nodeA.node[i].energy > 0)
        {
            int locNodeX = nodeA.node[i].x;
            int locNodeY = nodeA.node[i].y;

            // = [nodeArch.node(i).x, nodeArch.node(i).y];
            int countCH = clusterN.countCHs;

            //get the shortest distance to a cluster head
            int loc = 0;
            int minDis = 1000000;

            for(int j=0;j<countCH;j++)
            {
                int dist = sqrt( pow(locNodeX - clusterN.cNodes[j].locX, 2) + pow(locNodeY - clusterN.cNodes[j].locY, 2));

                if(dist < minDis)
                {
                    minDis = dist;
                    loc = j; 
                }
            }

            //[minDis, loc] = min(sqrt(sum((repmat(locNode, countCH, 1) - cluster.loc)^2))); //This wont work
            
            int minDisCH =  clusterN.cNodes[loc].no;

            if (minDis > d0)
            {
                nodeA.node[i].energy = nodeA.node[i].energy - ctrPacketLength * ETX + Emp * packetLength * (pow(minDis, 4));
            }
            else
            {
                nodeA.node[i].energy = nodeA.node[i].energy - ctrPacketLength * ETX + Efs * packetLength * (pow(minDis, 2));
            }

            if(minDis > 0)
            {
                nodeA.node[minDisCH].energy = nodeA.node[minDisCH].energy - ((ERX + EDA) * packetLength );
            }           
        }
    }
    clusterM.nodeA = nodeA;
    return clusterM;    
}
