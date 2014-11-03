#include "grid.h"
#include <math.h>

// Define default value for the grid
GRIDCELLSX = 1;
GRIDCELLSY = 1;

int getGridCell(double x, double y){
    double gx = x/XMAX;
    double gy = y/YMAX;

    int cx = (int) floor(gx*GRIDCELLSX);
    int cy = (int) floor(gy*GRIDCELLSY);
    /*
     * #########
     * # 0 # 1 #
     * #########
     * # 2 # 3 #
     * #########
     */
    return cy*GRIDCELLSY + cx;
}
