/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "../network/clusterModel.h"
#include "../network/roundArchitecture.h"
#include <math.h>
#include <stdio.h>

#ifndef DISSENERGY_H
#define DISSENERGY_H

ClusterModel* dissEnergyCH(ClusterModel* clusterM, RoundArch* roundA);
ClusterModel* dissEnergyNonCH(ClusterModel* clusterM, RoundArch* roundA);

#endif /* DISSENERGY_H */

