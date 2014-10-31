OPT = -O2

CC = gcc
CFLAGS = -Wall -g
LIBS = -lm #-fopenmp

all: target
target: fishing

OBJS = fishing.o util.o fish.o

fishing: $(OBJS)
	$(CC) -o fishing $(OBJS) $(OPT) $(LIBS) $(CFLAGS)


fishing.o: fishing.c fishing.h
	$(CC) -c  fishing.c -o fishing.o $(OPT) $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c -o util.o  $(OPT) $(CFLAGS)

fish.o: fish.c fish.h
	$(CC) -c fish.c -o fish.o $(OPT) $(CFLAGS)

clean:
	rm *.o fishing
