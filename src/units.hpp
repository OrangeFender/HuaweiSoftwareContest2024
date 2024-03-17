#include"common.hpp"
#define FETCH 0
#define RETURN 1
#define BOAT_MOVING 0
#define BOAT_LOADING 1
#define BOAT_PENDING 2

struct robots{
    point position;
    int status;//FETCH or RETURN

};

struct boat{
    int setoffTime;//出发时间，第几帧
    int capacity;
    int whichDock;
    point docks;
};

struct box{
    point position;
    int closestDock;
    int distances[MAP_SIZE_X][MAP_SIZE_Y];
    box();
};

struct dock{
    point position;
    int distances[MAP_SIZE_X][MAP_SIZE_Y];
    int status;
    dock();
};