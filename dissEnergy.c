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
    		nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Emp * packetLength * (distance ^ 4));
    	}
    	else
    	{
    		nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Efs * packetLength * (distance ^ 2));
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
    	if(strcmp(nodeA.node[i].type == 'N') && nodeA.node[i].dead == 0 && nodeA.node[i].energy > 0)
    	{
    		int countCH = clusterN.countCHs;

    		[minDis, loc] = min(sqrt(sum((repmat(locNode, countCH, 1) - cluster.loc)^2))); //This wont work
            
            int minDisCH =  cluster.cNodes[loc].no;

            if (minDis > d0)
            {
                nodeA.node[i].energy = nodeA.node[i].energy - ctrPacketLength * ETX + Emp * packetLength * (minDis ^ 4);
            }
            else
            {
                nodeA.node[i].energy = nodeA.node[i].energy - ctrPacketLength * ETX + Efs * packetLength * (minDis ^ 2);
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
