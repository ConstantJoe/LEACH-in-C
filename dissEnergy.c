#include "dissEnergy.h"

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
        float energy = clusterM->nodeA.node[chNo].energy;

        if(distance >= d0)
        {
            clusterM->nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Emp * packetLength * pow(distance, 2));
        }
        else
        {
            clusterM->nodeA.node[chNo].energy = energy - ((ETX+EDA) * packetLength + Efs * packetLength * pow(distance, 2));
        }
        clusterM->nodeA.node[chNo].energy = clusterM->nodeA.node[chNo].energy - ctrPacketLength * ERX * round(clusterM->nodeA.numNode / clusterM->numCluster);
    }

    return clusterM;
}

ClusterModel* dissEnergyNonCH(ClusterModel* clusterM, RoundArch* roundA)
{
    //something going wrong in here
    
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

            if(i==0){
                printf("Node 1 characteristics: dissEnergy 1 %f\r\n", clusterM->nodeA.node[0].energy);    
            }
            
            for(int j=0;j<countCH;j++)
            {
                double dist = sqrt( pow(locNodeX - clusterM->clusterN.cNodes[j].locX, 2) + pow(locNodeY - clusterM->clusterN.cNodes[j].locY, 2));

                if(i==0){
                    printf("dist %f\r\n", dist);    
                } 
                if(dist < minDis)
                {
                    minDis = dist;
                    loc = j; 
                }
            }


            
            int minDisCH =  clusterM->clusterN.cNodes[loc].no;

            if (minDis > d0)
            {
                if(i==0){
                    printf("minDis > d0\r\n");    
                    printf("energy lost: %f\r\n", ctrPacketLength * ETX + Emp * packetLength * (pow(minDis, 4)));
                    printf("minDis %f\r\n", minDis);
                }
                clusterM->nodeA.node[i].energy -= /*clusterM->nodeA.node[i].energy -*/ ctrPacketLength * ETX + Emp * packetLength * (pow(minDis, 4));
            }
            else
            {
                if(i==0){
                    printf("minDis <= d0\r\n");
                    printf("energy lost: %f\r\n", ctrPacketLength * ETX + Efs * packetLength * (pow(minDis, 2)));    //This sometimes is a very big number - going negative?
                    printf("minDis %f\r\n", minDis);
                }
                clusterM->nodeA.node[i].energy -= /*clusterM->nodeA.node[i].energy -*/ ctrPacketLength * ETX + Efs * packetLength * (pow(minDis, 2));
            }

            if(minDis > 0)
            {
                if(i==0){
                    printf("minDis > d0 CH\r\n");
                    printf("energy lost: %f\r\n", ((ERX + EDA) * packetLength ));    
                    //printf("minDis \f\r\n", minDis);
                }
                clusterM->nodeA.node[minDisCH].energy = clusterM->nodeA.node[minDisCH].energy - ((ERX + EDA) * packetLength );
            }

            if(i==0){
                printf("Node 1 characteristics: dissEnergy 2 %f\r\n", clusterM->nodeA.node[0].energy);    
            }           
        }
    }
    return clusterM;    
}
