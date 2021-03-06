#include "fish.h"
#include "boat.h"
#include "fishing.h"
#include "ocean.h"
#include "grid.h"


#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



void update(Boat boats[], Fish *fishes, int *fishesInCell,double dt){
    // This should all be separate for each of the processes
    // So one process each for each of the cells,
	// and a process each for the captains.
	for(int j = 0; j < GRIDCELLS; j++){
        for(int i =0; i < fishesInCell[j];i++){
            updateFish(boats,&fishes[FISHCOORD(j,i)],dt);
        }
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

    int rank;
    GRIDCELLSX = 2;
    GRIDCELLSY = 2;


    Ocean ocean;
    initOcean(&ocean);

	/* MPI_Status Stat; */ 
	MPI_Comm captains_chat;
	MPI_Group orig, captains;

	MPI_Init(&argc,&argv); 

	//MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
	

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    srand(rank*time(NULL));
    Fish *fishes = malloc(NUMFISHES);
    int fishesInCell = 0;
    Boat boatj;
    for(int i =0; i < NUMFISHES/4; i++)
    {
            Fish f = newFish();
            fishes[i] = f;
    }



    for(int i =0; i < 1000; i++){
        update(boats,fishes,fishesInCell,10);
        render(ocean,boats,fishes,fishesInCell);
        sleep(1);
    }
    free(fishes); // Lol

    MPI_Finalize(); 
    return 0;
}
