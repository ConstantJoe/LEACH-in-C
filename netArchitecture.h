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
	unsigned long init;
	unsigned long transfer;
	unsigned long receive;
	unsigned long freespace;
	unsigned long multipath;
	unsigned long aggr;
} Energy;

typedef struct NetArch
{
	struct Yard yard;
	struct Sink sink;
	struct Energy energy;
} NetArch;

struct NetArch newNetwork(int length, int width, int sinkX, int sinkY);

#endif /* NETARCHITECTURE_H */



