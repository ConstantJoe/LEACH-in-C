#include "netArchitecture.h"

struct NetArch* newNetwork(int width, int height, int sinkX, int sinkY)
{
	struct NetArch *netA = malloc(sizeof *netA); 

	if(width > 0)
	{
		netA->yard.width = width;
	}
	else
	{
		netA->yard.width = 100;
	}

	if(height > 0)
	{
		netA->yard.height = height;
	}
	else
	{
		netA->yard.height = 100;
	}

	if(sinkX > 0)
	{
		netA->sink.x = sinkX;
	}
	else
	{
		netA->sink.x = netA->yard.width/2;
	}

	if(sinkY > 0)
	{
		netA->sink.y = sinkY;
	}
	else
	{
		netA->sink.y = netA->yard.height/2;
	}

	netA->energy.init 		= 0.5; 
	netA->energy.transfer 	= 50*0.000000001;
	netA->energy.receive 	= 50*0.000000001;
	netA->energy.freespace 	= 10*0.000000000001;
	netA->energy.multipath 	= 0.0013*0.000000000001;
	netA->energy.aggr 		= 5*0.000000001;

	return netA;
}