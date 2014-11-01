#include "fish.h"
#include "boat.h"
#include "fishing.h"
#include "ocean.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void printSharpLine(Ocean ocean){
    printf("+");
    for(int j =0; j < ocean.width;j++){
        if (j == ocean.width/GRIDCELLSX){
            printf("+");
        }
        printf("-");
    }
    printf("+");
    printf("\n");
}
void render(Ocean ocean,Boat boats[], Fish fishes[]){
    clearOcean(&ocean);
    for(int i = 0; i < NUMFISHES; i++){
        addFishToOcean(&ocean,fishes[i]);
    }
    for(int i = 0; i < NUMBOATS; i++){
        addBoatToOcean(&ocean,boats[i]);
    }
    printf("Ocean w, h: %d, %d\n",ocean.width,ocean.height);
    printSharpLine(ocean);
    for(int i =0; i < ocean.height; i++){
        if (i == ocean.height/GRIDCELLSY){
            printSharpLine(ocean);
        }
        printf("|");
        for(int j =0; j < ocean.width;j++){
            if (j == ocean.width/GRIDCELLSX){
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


void update(Boat boats[], Fish fishes[],double dt){
    for(int i =0; i < NUMFISHES;i++){
        updateFish(boats,&fishes[i],dt);
    }
    for(int i = 0; i < NUMBOATS; i++){
        updateBoat(&boats[i]);
    }
}

void out (int n){
    printf("%d \n",n);
}

int main (int argc, char *argv[]) 
{
    srand(time(NULL));
    Ocean ocean;
    initOcean(&ocean);

    Fish fishes[NUMFISHES];

    for(int i =0; i < NUMFISHES; i++)
    {
            Fish f = newFish();
            fishes[i] = f;
    }

    Boat boats[NUMBOATS];

    for(int i =0; i < NUMBOATS; i++){
        boats[i] = newBoat();
    }

    for(int i =0; i < 1000; i++){
        update(boats,fishes,10);
        render(ocean,boats,fishes);
        sleep(1);
    }
    return 0;
}
