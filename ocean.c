#include "ocean.h"
#include "fish.h"
#include "fishing.h"
#include "util.h"
#include "grid.h"
#include "boat.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void printSharpLine(Ocean ocean){
    for(int j =0; j < ocean.width;j++){
        if (j % (ocean.width/GRIDCELLSX) == 0){
            printf("+");
        }
        printf("-");
    }
    printf("+");
    printf("\n");
}
void render(Ocean ocean,Boat boats[], Fish *fishes,int *fishesInCell)
{
    clearOcean(&ocean);
    for(int j = 0; j < GRIDCELLS; j++){
        for(int i = 0; i < fishesInCell[j]; i++){
            addFishToOcean(&ocean,fishes[FISHCOORD(j,i)]);
        }
    }
    for(int i = 0; i < NUMBOATS; i++){
        addBoatToOcean(&ocean,boats[i]);
    }
    printf("Ocean w, h: %d, %d\n",ocean.width,ocean.height);
    /* printSharpLine(ocean); */
    for(int i =0; i < ocean.height; i++){
        if (i % ( ocean.height/GRIDCELLSY) == 0){
            printSharpLine(ocean);
        }
        /* printf("|"); */
        for(int j =0; j < ocean.width;j++){
            if (j % ( ocean.width/GRIDCELLSX) == 0){
                printf("|");
            }
            int v = ocean.map[i][j];
            switch(v){
                case 0:
                    printf(".");
                    break;
                case 1:
                    printf("f");
                    break;
                case 2:
                    printf("b");
                    break;
                case 3:
                    printf("n");
                    break;
                default:
                    printf("%d",v);
                    break;
            }
        }
        printf("|\n");
    }
    printSharpLine(ocean);
}

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
    int x = (int) floor(OWIDTH*(f.x/XMAX));
    int y = (int) floor(OHEIGHT*(f.y/YMAX));
    ocean->map[y][x] = 1;
}

void addBoatToOcean(Ocean *ocean,Boat b)
{
    int x = (int) floor(OWIDTH*(b.x/XMAX));
    int y = (int) floor(OHEIGHT*(b.y/YMAX));
    int nx1 = (int) floor(OWIDTH*((b.net.x-b.net.width)/XMAX));
    int nx2 = (int) floor(OWIDTH*((b.net.x+b.net.width)/XMAX));
    int ny1 = (int) floor(OHEIGHT*((b.net.y-b.net.height)/YMAX));
    int ny2 = (int) floor(OHEIGHT*((b.net.y+b.net.height)/YMAX));
    ocean->map[ny1][nx1] = 3;
    ocean->map[ny2][nx1] = 3;
    ocean->map[ny1][nx2] = 3;
    ocean->map[ny2][nx2] = 3;
    ocean->map[y][x] = 2;
}
