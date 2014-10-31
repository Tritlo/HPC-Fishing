#include "ocean.h"
#include "util.h"
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
