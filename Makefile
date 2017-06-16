CC=gcc
CFLAGS=-I. -lm -g
DEPS = network/nodeArchitecture.h network/netArchitecture.h network/roundArchitecture.h leach_algorithm/leach.h energy/dissEnergy.h network/clusterModel.h network/newCluster.h
OBJ = start.o network/nodeArchitecture.o network/netArchitecture.o network/roundArchitecture.o leach_algorithm/leach.o energy/dissEnergy.o network/newCluster.o  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

leach: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) 

clean: 
	rm *.o
	rm leach
	rm ./leach_algorithm/*.o
	rm ./network/*.o
	rm ./energy/*.o
