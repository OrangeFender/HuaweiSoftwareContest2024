#include"common.hpp"


struct robots{
    point position;

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
    dock();
};