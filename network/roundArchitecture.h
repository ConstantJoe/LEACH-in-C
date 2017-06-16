/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include <stdlib.h>

#ifndef ROUNDARCHITECTURE_H
#define ROUNDARCHITECTURE_H

typedef struct RoundArch{
	int numRound;
	int packetLength;
	int ctrPacketLength;
} RoundArch;

struct RoundArch* newRound(int numRound, int packetLength, int ctrPacketLength);

#endif /* ROUNDARCHITECTURE_H */

