#include "fish.h"
#include "boat.h"
#include "fishing.h"
#include "ocean.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void render(Ocean ocean,Boat boats[], Fish fishes[]){
    clearOcean(&ocean);
    for(int i = 0; i < NUMSCHOOLS*FISHESINSCHOOL; i++){
        addFishToOcean(&ocean,fishes[i]);
    }
    for(int i = 0; i < NUMBOATS; i++){
        addBoatToOcean(&ocean,boats[i]);
    }
    printf("Ocean w, h: %d, %d\n",ocean.width,ocean.height);
    for(int j =0; j < ocean.width+2;j++){
        printf("#");
    }
    printf("\n");
    for(int i =0; i < ocean.height; i++){
        printf("#");
        for(int j =0; j < ocean.width;j++){
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
        printf("#\n");
    }
    for(int j =0; j < ocean.width+2;j++){
        printf("#");
    }
    printf("\n");
}

void updateBoat(Boat *boat){
    if(boat->net.caught > 0){
        printf("boat has %d in nets. \n", boat->net.caught);
        boat->net.caught = 0;
    }
}

/* We should probably use only fishes, and not
 * any of these school things. 
 * I've set FISHESINSCHOOl to 1
 * to emulate this, as the fishes in
 * the school don't have a logic to follow each other,
 * and it'd be quite a hassle to implement.
 */

void update(Boat boats[],School schools[], Fish fishes[],double dt){
    for(int i =0; i < NUMSCHOOLS; i++){
        updateSchool(boats,schools,fishes, i,dt);
    }
    for(int i = 0; i < NUMBOATS; i++){
        updateBoat(&boats[i]);
    }
}

void out (int n){
    printf("%d \n",n);
}

int main (int argc, char *argv[]) {
    srand(time(NULL));
    Ocean ocean;
    initOcean(&ocean);

    School schools[NUMSCHOOLS];
    for(int i =0; i < NUMSCHOOLS; i++){
        schools[i] = newSchool();
    }
    Fish fishes[FISHESINSCHOOL*NUMSCHOOLS];
    for(int j = 0; j < NUMSCHOOLS; j++){
        for(int i =0; i < FISHESINSCHOOL; i++){
            Fish f = newFish(j,schools);
            fishes[j*FISHESINSCHOOL+i] = f;
        }
    }

    Boat boats[NUMBOATS];

    for(int i =0; i < NUMBOATS; i++){
        boats[i] = newBoat();
    }

    for(int i =0; i < 1000; i++){
        update(boats,schools,fishes,10);
        render(ocean,boats,fishes);
        sleep(1);
    }
    return 0;
}
