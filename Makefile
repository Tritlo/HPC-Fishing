OPT = -O2

CC = c99
CFLAGS = -Wall 
LIBS = -lm #-fopenmp

all: target
target: fishing

OBJS = fishing.o util.o fish.o ocean.o

test: clean all
	./fishing

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

clean:
	rm *.o fishing
