OPT = -O2

CC = mpicc
CFLAGS = -Wall  -std=c99
LIBS = -lm #-fopenmp

test: clean all
	mpirun ./fishing

all: target
target: fishing

OBJS = fishing.o util.o fish.o ocean.o grid.o boat.o


fishing: $(OBJS)
	$(CC) -o fishing $(OBJS) $(OPT) $(LIBS) $(CFLAGS)


fishing.o: fishing.c fishing.h
	$(CC) -c  fishing.c -o fishing.o $(OPT) $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c -o util.o  $(OPT) $(CFLAGS)

fish.o: fish.c fish.h
	$(CC) -c fish.c -o fish.o $(OPT) $(CFLAGS)

ocean.o: ocean.c ocean.h
	$(CC) -c ocean.c -o ocean.o $(OPT) $(CFLAGS)

boat.o: boat.c boat.h
	$(CC) -c boat.c -o boat.o $(OPT) $(CFLAGS)

grid.o: grid.c grid.h
	$(CC) -c grid.c -o grid.o $(OPT) $(CFLAGS)

clean:
	rm -f *.o fishing
