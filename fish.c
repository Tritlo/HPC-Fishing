#include "fish.h"
#include "util.h"
#include <stdlib.h>

#define MINX -100
#define MAXX 100
#define MINY -100
#define MAXY 100
#define MINS 0.1
#define MAXS 0.3
#define PI 3.1415926535

#define XSD 5
#define YSD 5
#define SSD 0.02
#define DSD 0.3


Fish newFish(int school, School schools[]){
    School s = schools[school];
    Fish f;
    double sx = s.loc[0]; 
    double sy = s.loc[1]; 
    double fx = randNormal(sx,XSD);
    double fy = randNormal(sy,YSD);
    f.loc[0] = fx;
    f.loc[1] = fy;
    f.speed = randNormal(s.speed,SSD);
    f.dir = randNormal(s.dir,DSD);
    f.school = school;
    return f;

}

School newSchool(){
    School s;
    double x = randRange(MINX,MAXX);
    double y = randRange(MINY,MAXY);
    s.loc[0] = x;
    s.loc[1] = y;
    s.speed = randRange(MINS,MAXS);
    s.dir = randRange(0,2*PI);
    return s;
}
