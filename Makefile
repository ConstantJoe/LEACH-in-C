CC=gcc
CFLAGS=-I. -lm -g
DEPS = nodeArchitecture.h netArchitecture.h roundArchitecture.h leach.h dissEnergy.h clusterModel.h newCluster.h
OBJ = start.o nodeArchitecture.o netArchitecture.o roundArchitecture.o leach.o dissEnergy.o newCluster.o  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

leach: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) 
