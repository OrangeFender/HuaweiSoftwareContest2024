#include<iostream>

#include"units.hpp"

#include"common.hpp"

char map[MAP_SIZE_X][MAP_SIZE_Y];

dock docks[NUM_DOCKS] = {};
robot robots[NUM_ROBOTS] = {};
mapinfo M;

char okk[100] = {};

std::list<box> boxes;

int main(){
    for(int i=0;i<NUM_ROBOTS;i++){
        robots[i].id = i;
    }
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            scanf("%c", &map[i][j]);
        }
    }
    
    mapinfo M((char**)map);

    for(int i = 0; i < NUM_DOCKS; i++){
        docks[i].id = i;
        int x, y, s, v;
        scanf("%d %d %d", &x, &y, &s, &v);
        docks[i].position = point(x, y);
        docks[i].transport_time = s;
        docks[i].loading_speed = v;
        docks[i].setDistance(M);
    }
    
    
    scanf("%s", okk);
    printf("OK\n");
    fflush(stdout);

    for(int frame = 1; frame <= 15000; frame++){
        //读入数据
        int realframe,money;
        scanf("%d %d", &realframe, &money);
        int K;
        scanf("%d", &K);
        for(int i = 0; i < K; i++){
            int x, y, val;
            scanf("%d %d %d", &x, &y, &val);
            box b(point(x, y), val, realframe);
            boxes.push_back(b);
        }
        for(int i = 0; i < NUM_ROBOTS; i++){
            int goods, x, y, sts;
            scanf("%d %d %d %d", &goods, &x, &y, &sts);
            robots[i].initPerFrame(point(x, y));
            //robots[i].status = sts;
            if (frame==1){//第一帧匹配港口
                robots[i].findBestDock(docks, NUM_DOCKS);
            }
        }
        for(int i = 0; i < NUM_BOATS; i++){
            int sts, pos;
            scanf("%d %d", &sts, &pos);
            //
        }
        //处理数据
        for(int i = 0; i < NUM_ROBOTS; i++){
            if(robots[i].status == FETCH){
                robots[i].getBox();
            }
            if(robots[i].status == RETURN){
                robots[i].pullBox();
            }
            if(robots[i].status == PENDING){
                robots[i].findBestBox(boxes, frame);
            }
            robots[i].greedyGetNext();
        }
        //输出数据
        for(int i = 0; i < NUM_ROBOTS; i++){
            if(robots[i].pull){
                printf("pull %d\n", i);
            }
            if(robots[i].get){
                printf("get %d\n", i);
            }
            if(robots[i].next != NONE){
                printf("move %d %d\n",i , (int)robots[i].next);
            }
        }




        puts("OK");
        fflush(stdout);
    }
    return 0;
}