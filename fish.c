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
    f.loc[0] = fx;
    f.loc[1] = fy;
    double speed = randRange(MINS,MAXS);
    double dir = randRange(0,2*PI);
    f.vel[0] = speed*cos(dir);
    f.vel[1] = speed*sin(dir);
    return f;

}


void updateFish(Boat boats[],Fish *f, double dt)
{
    double fx = f->loc[0];
    double fy = f->loc[1];
    double vx = f->vel[0];
    double vy = f->vel[1];
    
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
    f->loc[0] = nx;
    f->loc[1] = ny;
    f->vel[0] = vx;
    f->vel[1] = vy;
}
