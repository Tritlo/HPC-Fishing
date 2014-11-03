#include "grid.h"
#include "boat.h"
#ifndef FISH
#define FISH

#define MINS 0.1
#define MAXS 0.3
#define XSD 1
#define YSD 2
#define VXSD 0.3
#define VYSD 0.6
#define CVXSD 0.1
#define CVYSD 0.2

typedef struct {
	double x;
	double y;
	double vx;
	double vy;
} Fish;




extern Fish newFish();
extern void updateFish(Boat boats[],Fish *f, double dt);
#endif
