#include "fish.h"
#include "fishing.h"
#include "ocean.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "boat.h"




Fish newFish()//
{
    Fish f;
    double fx = randRange(0,XMAX);
    double fy = randRange(0,YMAX);
    f.x = fx;
    f.y = fy;
    double speed = randRange(MINS,MAXS);
    double dir = randRange(0,2*PI);
    f.vx = speed*cos(dir);
    f.vy = speed*sin(dir);
    return f;

}


void updateFish(Boat boats[],Fish *f, double dt)
{
    double fx = f->x;
    double fy = f->y;
    double vx = f->vx;
    double vy = f->vy;
    
    vx = randNormal(vx,CVXSD);
    vy = randNormal(vy,CVYSD);
    double nx =  fx+vx*dt;
    double ny =  fy+vy*dt;

    //Bounce of ocean edges
    if (nx < 0 || nx > XMAX) vx *= -1;
    if ( ny < 0 || ny > YMAX) vy *= -1;
    for(int i = 0; i < NUMBOATS; i++){
        if(isInNet(boats[i].net,fx,fy)){
            boats[i].net.caught += 1;
            if(!isInNet(boats[i].net,nx,fy)){
                vx *=-1;
            }
            if(!isInNet(boats[i].net,fx,ny)){
                vy *=-1;
            }
        }
    }

    nx =  fx+vx*dt;
    ny =  fy+vy*dt;
    //int nextgridc = getGridCell(nx,ny);
    f->x = nx;
    f->y = ny;
    f->vx = vx;
    f->vy = vy;
}
