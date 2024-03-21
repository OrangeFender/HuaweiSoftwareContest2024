#include<iostream>

#include"units.hpp"

#include"common.hpp"

char map[MAP_SIZE_X][MAP_SIZE_Y];

dock docks[NUM_DOCKS] = {};
robot robots[NUM_ROBOTS] = {};
mapinfo M;

char okk[100] = {};
int main(){
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            scanf("%c", &map[i][j]);
        }
    }
    for(int i = 0; i < NUM_DOCKS; i++){
        int x, y, s, v;
        scanf("%d %d %d", &x, &y, &s, &v);
        docks[i].position = point(x, y);
        docks[i].transport_time = s;
        docks[i].loading_speed = v;
    }
    
    mapinfo M((char**)map);
    M.setBots(robots);
    //匹配机器人和港口
    
    scanf("%s", okk);
    printf("OK\n");
    fflush(stdout);

    while(1){

        //读入数据
        //处理数据
        //处理新物品,bfs
        //判断机器人是否在码头
        //如果是，
        //输出数据
    }

}