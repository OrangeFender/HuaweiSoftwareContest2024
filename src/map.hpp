#include "common.hpp"
#include "units.hpp"
#include<vector>

class mapinfo{
    int nowTime;
    dock docks[NUM_DOCKS];
    
    bool clearing[MAP_SIZE_X][MAP_SIZE_Y];//表示可以行走
    //int distances[NUM_DOCKS][MAP_SIZE_X][MAP_SIZE_Y];
    void dfs(point src, int distance,int distances[MAP_SIZE_X][MAP_SIZE_Y] );
    void bfs(point src,int distances[MAP_SIZE_X][MAP_SIZE_Y]);
    public:
    mapinfo(char map[MAP_SIZE_X][MAP_SIZE_Y]);//初始化码头位置和每个点的距离
    //int getDistance(point p, int dockIndex);
};