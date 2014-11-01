#include "fish.h"
#include "grid.h"
#include "boat.h"
#define OWIDTH 80
#define OHEIGHT 40


typedef struct {
    int map[OHEIGHT][OWIDTH];
    int width;
    int height;
} Ocean;


extern void initOcean(Ocean* ocean);
extern void addFishToOcean(Ocean* ocean,Fish f);
extern void addBoatToOcean(Ocean *ocean,Boat b);
extern void clearOcean(Ocean* ocean);
