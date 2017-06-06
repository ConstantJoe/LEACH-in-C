#include <stdlib.h>

#ifndef NETARCHITECTURE_H
#define NETARCHITECTURE_H

typedef struct Yard
{
	int width;
	int height;
} Yard;

typedef struct Sink
{
	int x;
	int y;
} Sink;

typedef struct Energy
{
	double init;
	double transfer;
	double receive;
	double freespace;
	double multipath;
	double aggr;
} Energy;

typedef struct NetArch
{
	struct Yard yard;
	struct Sink sink;
	struct Energy energy;
} NetArch;

struct NetArch* newNetwork(int length, int width, int sinkX, int sinkY);

#endif /* NETARCHITECTURE_H */



