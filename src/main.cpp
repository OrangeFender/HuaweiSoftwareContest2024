#include<iostream>

#include"units.hpp"

#include"common.hpp"

#include <fstream>


char m[MAP_SIZE_X+5][MAP_SIZE_Y+5];

dock docks[NUM_DOCKS] = {};
robot robots[NUM_ROBOTS] = {};
boat boats[NUM_BOATS]={};
//mapinfo M;

char okk[100] = {};

std::list<box> boxes;

int main(){
    
    std::ofstream debugFile("debug.txt");

    for(int i=0;i<NUM_ROBOTS;i++){
        robots[i].id = i;
    }
    for(int i = 0; i < MAP_SIZE_X; i++){
        scanf("%s", m[i]);
    }
    
    mapinfo M(m);

    for(int i = 0; i < NUM_DOCKS; i++){
        scanf("%d",&docks[i].id);
        int x, y, s, v;
        scanf("%d %d %d %d", &x, &y, &s, &v);
        docks[i].position = point(x, y);
        docks[i].transport_time = s;
        docks[i].loading_speed = v;
        docks[i].setDistance(M);
        // for(int ii=0;ii<MAP_SIZE_X;ii++){
        //     for(int jj=0;jj<MAP_SIZE_Y;jj++){
        //         std::cout<<docks[i].distances[ii][jj]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }
    }
    
    scanf("%d",&boats[0].capacity);
    
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
            boxes.push_back(b);//将箱子加入箱子列表
        }
        for(int i = 0; i < NUM_ROBOTS; i++){
            int have, x, y, sts;
            scanf("%d %d %d %d", &have, &x, &y, &sts);
            //debugFile<<"id"<<i<<" x:"<<x<<" y:"<<y<<std::endl;
            robots[i].initPerFrame((bool) have,point(x, y));
            //debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<std::endl;
            //robots[i].status = sts;
            if (frame==1){//第一帧匹配港口
                robots[i].findBestDock(docks, NUM_DOCKS);
                std::cerr<<"dock "<<robots[i].targetDock->id<<std::endl;
                // for(int ii=0;ii<MAP_SIZE_X;ii++){
                //     for(int jj=0;jj<MAP_SIZE_Y;jj++){
                //         std::cerr<<robots[i].targetDock->distances[ii][jj]<<" ";
                //     }
                //     std::cerr<<std::endl;
                // }
            }
        }
        for(int i = 0; i < NUM_BOATS; i++){
            int sts, pos;
            scanf("%d %d\n", &sts, &pos);
            //
        }
        scanf("%s", okk);
        //处理数据
        for(int i = 0; i < NUM_ROBOTS; i++){
            if(robots[i].status == FETCH){
                robots[i].getBox();
            }
            if(robots[i].status == RETURN){
                robots[i].pullBox();
            }
            if(robots[i].status == PENDING){
                //debugFile<<"boxsize"<<boxes.size()<<std::endl;
                robots[i].findBestBox(boxes, realframe,M);
            }
            robots[i].greedyGetNext();
            
            if(robots[i].status == FETCH){
                //debugFile<<"boxpos"<<robots[i].targetBox.position.x<<" "<<robots[i].targetBox.position.y<<std::endl;
                //debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<" Dis:"<<robots[i].position.getMapValue(robots[i].boxBFS)<<" dir:"<<robots[i].next<<" nextDis:"<<robots[i].position.moveOneStep(robots[i].next).getMapValue(robots[i].boxBFS)<<std::endl;        
            }
            //debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<" Dis:"<<robots[i].position.getMapValue(robots[i].targetDock->distances)<<" dir:"<<robots[i].next<<" nextDis:"<<robots[i].position.moveOneStep(robots[i].next).getMapValue(robots[i].targetDock->distances)<<std::endl;
        }

        bool flag = false;
        do{
            bool Vec[NUM_ROBOTS];
            for(int i = 0; i < NUM_ROBOTS; i++){
                Vec[i] = false;//初始化
            }
            flag = false;
            for(int i = 0; i < NUM_BOATS; i++){
                if(robots[i].Collision(robots, NUM_ROBOTS, Vec))flag = true;
            }
            for(int i = 0; i < NUM_ROBOTS; i++){
                if(Vec[i]){
                    debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<std::endl;
                    debugFile<<"dir"<<robots[i].next<<std::endl;
                    robots[i].RandomMove(M);
                    debugFile<<"dirafterRandom"<<robots[i].next<<std::endl;
                }
            }
        }while (flag);
        
        

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




        printf("OK\n");
        fflush(stdout);
    }
    return 0;
}