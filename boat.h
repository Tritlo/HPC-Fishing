#ifndef BOAT
#define BOAT

#define NUMBOATS 2

#define NETWIDTH 30
#define NETHEIGHT 50
#define MAXINNET 3

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
extern void updateBoat(Boat *boat);



#endif
