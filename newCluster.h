#include "clusterModel.h"
#include "leach.h"
#include <math.h>
#include <stdio.h>

#ifndef NEWCLUSTER_H
#define NEWCLUSTER_H

int clusterOptimum(NetArch* netA, NodeArch* nodeA, double dBS);

ClusterModel* newCluster(NetArch* netA, NodeArch* nodeA);

ClusterModel* clusterRun(ClusterModel* clusterM, int roundNo, float p_numCluster);

#endif /* NEWCLUSTER_H */
