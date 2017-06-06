#include "clusterModel.h"
#include <math.h>
#include <stdio.h>

#ifndef LEACH_H
#define LEACH_H

float prob(int roundNo, float p);

struct ClusterModel* leach(ClusterModel* clusterM, int nodeId);

#endif /* LEACH_H */



