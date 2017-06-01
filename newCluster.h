#include "clusterModel.h"
#include "leach.h"
#include <math.h>
#include <stdio.h>

#ifndef NEWCLUSTER_H
#define NEWCLUSTER_H

int clusterOptimum(NetArch netA, NodeArch nodeA, float dBS);

ClusterModel newCluster(NetArch netA, NodeArch nodeA, int roundNo, int p_numCluster);

#endif /* NEWCLUSTER_H */
