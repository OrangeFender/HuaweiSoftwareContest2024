#include<iostream>

#include"units.hpp"

#include"common.hpp"

#include <fstream>


char m[MAP_SIZE_X+5][MAP_SIZE_Y+5];

dock docks[NUM_DOCKS] = {};
robot robots[NUM_ROBOTS] = {};
boat boats[NUM_BOATS];
int boat::capacity = 0;
//mapinfo M;

char okk[100] = {};

std::list<box> boxes;

int main(){
    //初始化随机数种子
    srand(time(0));

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
        debugFile<<"dock"<<i<<docks[i].transport_time<<" "<<v<<std::endl;
        docks[i].loading_speed = v;
        docks[i].setDistance(M);
        docks[i].calcVRobot();
        // for(int ii=0;ii<MAP_SIZE_X;ii++){
        //     for(int jj=0;jj<MAP_SIZE_Y;jj++){
        //         std::cout<<docks[i].distances[ii][jj]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }
    }

    scanf("%d",&boat::capacity);
    debugFile<<"capacity"<<boat::capacity<<std::endl;

    for(int i = 0; i < NUM_BOATS; i++){
        boats[i]=boat(1,-1,-1,i,-1,BOAT_LOADING,0);
    }

    boat_bind_dock(boats, docks);

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

        //debugFile<<"frame"<<frame<<"K"<<K<<std::endl;
        for(int i = 0; i < NUM_ROBOTS; i++){
            //debugFile<<"id"<<i<<std::endl;
            int have, x, y, sts;
            scanf("%d %d %d %d", &have, &x, &y, &sts);
            //debugFile<<"id"<<i<<" x:"<<x<<" y:"<<y<<std::endl;
            robots[i].initPerFrame((bool) have,point(x, y));
            //debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<std::endl;
            //robots[i].status = sts;
            if (frame==1){//第一帧匹配港口
                robots[i].findBestDock(docks, NUM_DOCKS);
                if(robots[i].targetDock==NULL){
                    //debugFile<<"robot "<<i<<" sleeping"<<std::endl;
                }
                //debugFile<<"dock "<<robots[i].targetDock->id<<std::endl;
                // for(int ii=0;ii<MAP_SIZE_X;ii++){
                //     for(int jj=0;jj<MAP_SIZE_Y;jj++){
                //         std::cerr<<robots[i].targetDock->distances[ii][jj]<<" ";
                //     }
                //     std::cerr<<std::endl;
                // }
            }

            // if(realframe==45){
            //     if(robots[i].status==RETURN&&robots[i].haveBox==false){
            //         robots[i].status==PENDING;
            //     }
            // }

            if(frame==10000){
                if(robots[i].targetDock!=NULL){
                    debugFile<<"id"<<i<<"frienddock"<<robots[i].targetDock->friendDock<<std::endl;
                    if(robots[i].targetDock->friendDock!=NULL){
                        robots[i].targetDock=robots[i].targetDock->friendDock;
                        robots[i].status=RETURN;
                        debugFile<<"id"<<i<<"changed"<<std::endl;
                    }
                }

            }

        }
        for(int i = 0; i < NUM_BOATS; i++){
            int sts, pos;
            scanf("%d %d\n", &sts, &pos);
            boats[i].boat_ope(sts, pos, realframe, docks[boats[i].whichDock1], docks[boats[i].whichDock2],10000);//返回值 0:不操作 1:去港口1 2:去港口2 3:去虚拟点
        }
        scanf("%s", okk);
        //处理数据
        for(int i = 0; i < NUM_ROBOTS; i++){
            if(robots[i].targetDock==NULL){
                //debugFile<<"robot "<<i<<" sleeping"<<std::endl;
                continue;
            }
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
            for(int i = 0; i < NUM_ROBOTS; i++){
                if(robots[i].targetDock==NULL)continue;
                if(robots[i].Collision(robots, NUM_ROBOTS, Vec))flag = true;
                if(robots[i].narrowCollision(robots[i].position.moveOneStep(robots[i].next), opposite(robots[i].next), robots, NUM_ROBOTS,M)){
                    Vec[i] = true;
                    flag = true;
                }
            }
            for(int i = 0; i < NUM_ROBOTS; i++){
                if(robots[i].targetDock==NULL)continue;
                if(Vec[i]){
                    //debugFile<<"id"<<i<<" x:"<<robots[i].position.x<<" y:"<<robots[i].position.y<<std::endl;
                    //debugFile<<"dir"<<robots[i].next<<std::endl;
                    robots[i].RandomMove(M);
                    //debugFile<<"Frame"<<realframe<<"dirafterRandom"<<robots[i].next<<std::endl;
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
        for(int i = 0; i < NUM_BOATS; i++){
            switch (boats[i].operation)
            {
            case BOAT_NONE:
                break;
            case BOATGO_DOCK1:
                printf("ship %d %d\n", i, boats[i].whichDock1);
                break;
            case BOATGO_DOCK2:
                printf("ship %d %d\n", i, boats[i].whichDock2);
                break;
            case BOATGO_VIRTUAL:
                printf("go %d\n", i);
                break;
            }
        }
        printf("OK\n");
        fflush(stdout);

        int sum=0;
        if (realframe==14980){
            for(int i =0;i<NUM_DOCKS;i++){
                sum+=docks[i].value_summary;
                debugFile<<"time"<<frame<<std::endl;
                debugFile<<"dock"<<i<<" "<<docks[i].counter<<" "<<docks[i].counter_summary<<" "<<docks[i].value_summary<<"Vrobot"<<docks[i].vRobot<<std::endl;
            }
            debugFile<<"sum "<<sum<<std::endl;
        }
    
    }
    return 0;
}