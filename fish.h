#ifndef FISH
#define FISH

#define XMAX 1000
#define YMAX 1000
#define MINS 0.1
#define MAXS 0.3
#define XSD 1
#define YSD 2
#define VXSD 0.3
#define VYSD 0.6
#define CVXSD 0.1
#define CVYSD 0.2

typedef struct {
    double loc[2];
    double vel[2];   //velocity
    int school;          //What group the fish is in.
} Fish;


typedef struct {
    double loc [2]; //Location of school;
    double vel[2];
} School;


extern School newSchool();
extern Fish newFish(int school, School schools[]);
extern void updateSchool(School school[],Fish fishes[], int schoolid,double dt);
#endif
