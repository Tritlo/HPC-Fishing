#include "boat.h"
#include <stdlib.h>
#include "fish.h"
#include "util.h"


Boat newBoat()
{
    Boat b;
    double x = randRange(0,XMAX);
    double y = randRange(0,YMAX);
    Net net;
    b.loc[0] = x;
    b.loc[1] = y;
    net.loc[0] = x;
    net.loc[1] = y;
    net.width = 30;
    net.height = 50;
    b.net = net;
    b.net.caught = 0;
    return b;
}


int isInNet(Net net,double fx, double fy)
{
    double nx = net.loc[0];
    double ny = net.loc[1];
    double w = net.width;
    double h = net.height;
    return nx - w < fx && fx < nx + w && ny-h < fy && fy < ny + h;
}

