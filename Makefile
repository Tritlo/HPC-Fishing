OPT = -O2

CC = mpicc
CFLAGS = -Wall  -std=c99
LIBS = -lm #-fopenmp


test: clean all
	mpirun  -n 16 ./fishing
	./render.py

all: target
target: fishing

OBJS = fishing.o

fishing: $(OBJS)
	$(CC) -o fishing $(OBJS) $(OPT) $(LIBS) $(CFLAGS)

fishing.o: fishing.c
	$(CC) -c  fishing.c -o fishing.o $(OPT) $(CFLAGS)


clean:
	rm -f *.o fishing *output
