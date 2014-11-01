#ifndef BOAT
#define BOAT


typedef struct {
    double loc[2];
    double width;
    double height;
    int caught;
} Net;

typedef struct {
    double loc[2];
    Net net;
} Boat;

extern int isInNet(Net net,double fx, double fy);
extern Boat newBoat();

#define NUMBOATS 2

#endif
