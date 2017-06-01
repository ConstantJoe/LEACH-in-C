CC=gcc
CFLAGS=-I.
DEPS = nodeArchitecture.h netArchitecture.h roundArchitecture.h leach.h dissEnergy.h clusterModel.h 
OBJ = start.o nodeArchitecture.o netArchitecture.o roundArchitecture.o leach.o dissEnergy.o clusterModel.o  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)