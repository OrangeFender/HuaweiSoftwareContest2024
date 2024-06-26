#ifndef MAP_HPP
#define MAP_HPP

#include "common.hpp"
#include <vector>

class mapinfo{
    int nowTime;
    
    //int distances[NUM_DOCKS][MAP_SIZE_X][MAP_SIZE_Y];
    
public:
    bool clearing[MAP_SIZE_X][MAP_SIZE_Y];//表示可以行走
    
    void dfs(point src, int distance,int distances[MAP_SIZE_X][MAP_SIZE_Y] );
    void bfs(point src,int distances[MAP_SIZE_X][MAP_SIZE_Y]);
    mapinfo(char m[MAP_SIZE_X+5][MAP_SIZE_Y+5]);//初始化码头位置和每个点的距离
    int degree(point p);//计算一个点的度数
    //int getDistance(point p, int dockIndex);
    //void setBots(robot* bots);
};

#endif // MAP_HPP
