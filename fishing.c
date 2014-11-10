// HPC Fishing, by Matthías Páll Gissurarson
//
// Run with make to get a pretty rendering
// of the outputted binary files via python.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdbool.h>
#include <time.h>

int randRange(int low, int high){
    int r =  rand()/(RAND_MAX/(high-low)) + low;
    return r;
}


int main (int argc, char** argv) {
	int rank, size;
    int dims[2], periods[2];
    int coords[2]; // = malloc(2*sizeof(int));
    int fromcoords[2];
    int source,dest;

    int captains[2];


    int reorder;
    MPI_Comm comm_2d;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Request capreq,fishreq,tickstofullreq;

    //Seed random for each rank.
    srand((rank+1)*time(NULL));

	dims[0]=5, dims[1] = 5;
    captains[0] = 15;
    captains[1] = 23;
    int direction = 0;
    int maxinnets = 5;

    int fishesincell = 0;
    int nextfishesincell;

    MPI_Info info;
    MPI_Info_create(&info);
    MPI_File ffh,cfh,dfh;


    

    int numticks = 20;
	if(rank == 0){
		//Print the header for the output file
		//and spawn a single fish in rank 0.
        char *tickbuf = "20";
        //puts(tickbuf); 
        //puts("tick\trank\tcoords\tiscaptain\tspawned\tnow\n");
		fishesincell = 1;
    }

    int iscaptain = false;
    int caughtfishes = 0;
    int othercaptaincaughtfishes;

    //Set the captains.
    //
    if (rank == captains[0] || rank == captains[1]){
    	iscaptain = true;
    }

    int capnum;
    //Know who the other captain is.
    if(rank == captains[0]){
    	capnum = 0;

    } else if (rank == captains[1]){
    	capnum = 1;
    }

	periods[0]=true; periods[1]=true;
	reorder = false;
    MPI_Status status;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &comm_2d);
	MPI_Cart_coords(comm_2d, rank, 2, coords); //Where am I?

    //From whom do I recieve fish? To whom do I send fish? 
    // This cell recieves fishes from source, and send fish to dest.
	MPI_Cart_shift(comm_2d, 0, 1, &source, &dest);
    //1 means the fishes are swimming down, 0 means that they are swimming right    .
    int rc = MPI_File_open(comm_2d,"fishoutput", MPI_MODE_CREATE|MPI_MODE_RDWR,info,&ffh);
    rc = MPI_File_open(MPI_COMM_WORLD,"captainsoutput", MPI_MODE_CREATE|MPI_MODE_RDWR,info,&cfh);
    rc = MPI_File_open(MPI_COMM_WORLD,"dataoutput", MPI_MODE_CREATE|MPI_MODE_RDWR,info,&dfh);
    int netsfull = false;
    int tickstofull;
    for(int i =0; i< numticks; i++){
    	//Every 3 ticks we change the direction.
    	//And recieve a new source/destination.
    	char buf[255];
    	int ibuf[7];

    	int spawned = false;
    	int nocaptain = true;
    	if (i % 3 == 0 && i != 0){
    	    direction = direction == 0 ? 1 : 0;
	        MPI_Cart_shift(comm_2d, direction, 1, &source, &dest);
        }
        //Send our fishes, and recieve the next fishes.
        //Do this async.
        MPI_Isend(&fishesincell,1,MPI_INT,dest,13,comm_2d,&fishreq);
        MPI_Recv(&nextfishesincell,1,MPI_INT,source,13,comm_2d,&status);

        //MPI_Sendrecv(&fishesincell,1,MPI_INT,dest,13,&nextfishesincell,1,MPI_INT,source,13,comm_2d,&status);
        //Update our fishes.
        fishesincell = nextfishesincell;

        if(coords[direction] == 0  && rand() < RAND_MAX/4){
            //Fishes randomly spawn with probability 1/4
            //in coords where the fish can start swimming.
            fishesincell++;
            spawned = true;
        }


        if(iscaptain && !netsfull){
        	//The captains remove the fishes from the cell.
        	caughtfishes += fishesincell;
        	fishesincell = 0;
        }
        if(!netsfull && caughtfishes >= maxinnets){
        	netsfull = true;
        	tickstofull = i;
            MPI_Isend(&tickstofull,1,MPI_INT,0,16,MPI_COMM_WORLD,&tickstofullreq);
        }

        if(iscaptain && !netsfull){
        	nocaptain = false;
        }

        ibuf[0] = i;
        ibuf[1] = rank;
        ibuf[2] = coords[0];
        ibuf[3] = coords[1];
        ibuf[4] = !nocaptain;
        ibuf[5] = spawned;
        ibuf[6] = fishesincell;

        sprintf(buf,"%d\t%d\t%d,%d\t%d\t%d\t%d\n",i,rank,coords[0],coords[1],!nocaptain,spawned,fishesincell);
        //puts(buf);
        MPI_File_write_ordered(ffh,ibuf,7,MPI_INT,&status);
        if(iscaptain){
        	int capbuf[5];
        	//The captains tell eachother about how many fishes they've
        	//Caught, and then write in their log how many each has.
        	//We don't need to wait for the other captain to recieve the
        	//messsge.
        	MPI_Isend(&caughtfishes,1,MPI_INT,captains[(capnum+1)%2],15,MPI_COMM_WORLD,&capreq);
        	MPI_Recv(&othercaptaincaughtfishes,1,MPI_INT,captains[(capnum+1)%2],15,MPI_COMM_WORLD,&status);
        	//MPI_Wait(&reqs[(capnum+1)%2],&status);
        	/*MPI_Sendrecv(&caughtfishes,1,MPI_INT,captains[(capnum+1)%2],15,
        	             &othercaptaincaughtfishes,
        	             1,MPI_INT,captains[(capnum+1)%2],
        	             15,MPI_COMM_WORLD,&status);*/
        	capbuf[0] = i;
        	capbuf[1] = capnum;
        	capbuf[2] = rank;
        	capbuf[3] = caughtfishes;
        	capbuf[4] = othercaptaincaughtfishes;

        	sprintf(buf,"%d\t: Captains log, tick %d: I'm captain %d in cell %d and I've caught %d fishes while the captain in cell %d has caught %d fishes\n",i,i,capnum,rank,caughtfishes,captains[(capnum+1)%2],othercaptaincaughtfishes);

            MPI_File_write_shared(cfh,capbuf,5,MPI_INT,&status);
        	//puts(buf);
        }

            //We wait a bit before proceeding.
    }

    //Collect average tickstofull.
    int sectstowait = 1;
    if(rank == 0){
        char buf[63];
        int totaltickstofull = 0;
        for(int i =0; i < 2; i++){
            int logtickstofull = numticks;
            MPI_Irecv(&logtickstofull,1,MPI_INT,captains[i],16,MPI_COMM_WORLD,&tickstofullreq);
            int flag = false;
            // Try for 1 secs, else assume that
            // the fisher did not fill its nets.
            for(int j = 0; j < sectstowait; j++){
                MPI_Test(&tickstofullreq,&flag,&status);
                if(flag) break;
                sleep(1);
            }

            totaltickstofull += logtickstofull;
        }
        sprintf(buf,"%.2f ticks to full on average",totaltickstofull/(2.0));
        int obuf[4];
        
        int numcaptains = 2;
        obuf[0] = numticks;
        obuf[1] = dims[0]*dims[1];
        obuf[2] = totaltickstofull;
        obuf[3] = numcaptains;
        MPI_File_write(dfh,obuf,4,MPI_INT,&status);
        //puts(buf);
    }

    rc = MPI_File_close(&ffh);
    rc = MPI_File_close(&dfh);
    rc = MPI_File_close(&cfh);
    MPI_Finalize();

	return 0;

}
