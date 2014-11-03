#ifndef GRID
#define GRID

#define XMAX 1000
#define YMAX 1000

//#define GRIDCELLSX 2
//#define GRIDCELLSY 2
#define GRIDCELLS GRIDCELLSX*GRIDCELLSY


#define FISHCOORD(cell,fish) (cell)*NUMFISHES + (fish)


extern int GRIDCELLSX;
extern int GRIDCELLSY;

extern int getGridCell(double x, double y);

#endif
