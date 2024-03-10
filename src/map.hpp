#include "common.hpp"
#include "defs.h"


class mapinfo{
    point dockpoint[NUM_DOCKS];//码头位置
    bool clearing[MAP_SIZE_X][MAP_SIZE_Y];
    int distances[NUM_DOCKS][MAP_SIZE_X][MAP_SIZE_Y];
    void dfs(point p, int dockIndex, int distance );
    public:
    mapinfo(char map[MAP_SIZE_X][MAP_SIZE_Y]);//初始化码头位置
    int getDist2Dock(point A, int dock);
};