/*
 *  Implementation of Mohammad Hossein Homaei's LEACH simulator, in C.
 *  Joseph Finnegan
 *  joseph.finnegan@cs.nuim.ie
 *  2017
 */

#include "roundArchitecture.h"

/*
 *	Generate handler for overall experiment details.
 */
struct RoundArch* newRound(int numRound, int packetLength, int ctrPacketLength)
{
	struct RoundArch *roundA = malloc(sizeof *roundA); 

	if(numRound == 0)
	{
		roundA->numRound = 9999;	
	}
	else
	{
		roundA->numRound = numRound;	
	}
	
	if(packetLength == 0)
	{
		roundA->packetLength= 6400;
	} 
	else
	{
		roundA->packetLength = packetLength;	
	}

	if(ctrPacketLength == 0)
	{
		roundA->ctrPacketLength = 6400;
	} 
	else
	{
		roundA->ctrPacketLength = ctrPacketLength;	
	}
	
	return roundA;
}