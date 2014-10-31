#include "fish.h"
#include "fishing.h"
#include "ocean.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>





Fish newFish(int school, School schools[]){
    School s = schools[school];
    Fish f;
    double sx = s.loc[0]; 
    double sy = s.loc[1]; 
    double svx = s.vel[0]; 
    double svy = s.vel[1]; 
    double fx = max(0,randNormal(sx,XSD));
    double fy = max(0,randNormal(sy,YSD));
    f.loc[0] = fx;
    f.loc[1] = fy;
    f.vel[0] = randNormal(svx,VXSD);
    f.vel[1] = randNormal(svy,VYSD);
    f.school = school;
    return f;

}

School newSchool(){
    School s;
    double x = randRange(0,XMAX);
    double y = randRange(0,YMAX);
    s.loc[0] = x;
    s.loc[1] = y;
    double speed = randRange(MINS,MAXS);
    double dir = randRange(0,2*PI);
    s.vel[0] = speed*cos(dir);
    s.vel[1] = speed*sin(dir);
    return s;
}

void updateFish(Fish *f, double dt){
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
    nx =  fx+vx*dt;
    ny =  fy+vy*dt;
    f->loc[0] = nx;
    f->loc[1] = ny;
    f->vel[0] = vx;
    f->vel[1] = vy;
    

}

void updateSchool(School school[],Fish fishes[], int schoolid,double dt)
{
    double mx =0, my = 0, mvx =0, mvy =0;
    for(int i =0; i < FISHESINSCHOOL;i++){
        int ind = schoolid*FISHESINSCHOOL + i;
        updateFish(&fishes[ind],dt);
        mx += fishes[ind].loc[0];
        my += fishes[ind].loc[1];
        mvx += fishes[ind].vel[0];
        mvy += fishes[ind].vel[1];
    }
    school[schoolid].loc[0] = mx/FISHESINSCHOOL;
    school[schoolid].loc[1] = my/FISHESINSCHOOL;
    school[schoolid].vel[0] = mvx/FISHESINSCHOOL;
    school[schoolid].vel[1] = mvy/FISHESINSCHOOL;

}

