#ifndef BOAT
#define BOAT

#define NUMBOATS 2

#define NETWIDTH 30
#define NETHEIGHT 50
#define MAXINNET 3

typedef struct {
	double x;
	double y;
    double width;
    double height;
    int caught;
    int maxCaught;
} Net;

typedef struct {
	double x;
	double y;
    Net net;
} Boat;

extern int isInNet(Net net,double fx, double fy);
extern Boat newBoat();
extern void updateBoat(Boat *boat);



#endif
