#include "fish.h"
#include "boat.h"
#include "fishing.h"
#include "ocean.h"


#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



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

	/* MPI_Status Stat; */ 
	MPI_Init(&argc,&argv); 

	//MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 

	/* MPI_Comm_rank(MPI_COMM_WORLD, &rank); */ 

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

    MPI_Finalize(); 
    return 0;
}
