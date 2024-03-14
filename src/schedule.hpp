#include"common.hpp"
#include"defs.h"

struct robots{
    point position;

};

struct boats{
    int setoffTime;
    int capacity;
    int whichDock;
    point docks;
};

struct box{
    point position;
    int closestDock;
};
