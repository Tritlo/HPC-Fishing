#include "boat.h"
#include <stdlib.h>
#include "fish.h"
#include "util.h"
#include <stdio.h>


Boat newBoat()
{
    Boat b;
    double x = randRange(NETWIDTH,XMAX-NETWIDTH);
    double y = randRange(NETHEIGHT,YMAX-NETHEIGHT);
    Net net;
    b.x = x;
    b.y = y;
    net.x = x;
    net.y = y;
    net.width = NETWIDTH;
    net.height = NETHEIGHT;
    b.net = net;
    b.net.caught = 0;
    b.net.maxCaught = 0;
    return b;
}

void updateBoat(Boat *boat)
{
    if(boat->net.caught > boat->net.maxCaught)
    {
        boat->net.maxCaught = boat->net.caught;
    }
    boat->net.caught = 0;
    printf("I've caught %d fish!\n", boat->net.maxCaught);
}

int isInNet(Net net,double fx, double fy)
{
    double nx = net.x;
    double ny = net.y;
    double w = net.width;
    double h = net.height;
    return nx - w < fx && fx < nx + w && ny-h < fy && fy < ny + h;
}

