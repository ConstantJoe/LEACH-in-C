#ifndef ROUNDARCHITECTURE_H
#define ROUNDARCHITECTURE_H

typedef struct RoundArch{
	int numRound;
	int packetLength;
	int ctrPacketLength;
} RoundArch;

struct RoundArch newRound(int numRound, int packetLength, int ctrPacketLength);

#endif /* ROUNDARCHITECTURE_H */

