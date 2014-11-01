#include "ocean.h"
#include "util.h"
#include "grid.h"
#include "boat.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void clearOcean(Ocean *ocean)
{
    for(int i =0; i < ocean->height; i++){
        for(int j =0; j < ocean->width;j++){
            ocean->map[i][j] = 0;
        }
    }
}

void initOcean(Ocean* ocean)
{
    ocean->width = OWIDTH;
    ocean->height = OHEIGHT;
    printf("%d \n",ocean->width);
    printf("%d \n",ocean->height);
    clearOcean(ocean);
}

void addFishToOcean(Ocean *ocean,Fish f)
{
    int x = (int) floor(OWIDTH*(f.loc[0]/XMAX));
    int y = (int) floor(OHEIGHT*(f.loc[1]/YMAX));
    ocean->map[y][x] = 1;
}

void addBoatToOcean(Ocean *ocean,Boat b)
{
    int x = (int) floor(OWIDTH*(b.loc[0]/XMAX));
    int y = (int) floor(OHEIGHT*(b.loc[1]/YMAX));
    int nx1 = (int) floor(OWIDTH*((b.net.loc[0]-b.net.width)/XMAX));
    int nx2 = (int) floor(OWIDTH*((b.net.loc[0]+b.net.width)/XMAX));
    int ny1 = (int) floor(OHEIGHT*((b.net.loc[1]-b.net.height)/YMAX));
    int ny2 = (int) floor(OHEIGHT*((b.net.loc[1]+b.net.height)/YMAX));
    ocean->map[ny1][nx1] = 3;
    ocean->map[ny2][nx1] = 3;
    ocean->map[ny1][nx2] = 3;
    ocean->map[ny2][nx2] = 3;
    ocean->map[y][x] = 2;
}
