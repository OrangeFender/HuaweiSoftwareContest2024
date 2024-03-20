#include"common.hpp"
//关于机器人的状态
#define FETCH 0
#define RETURN 1
#define PENDING 2

#include<list>


struct boat{
    int setoffTime;//出发时间，第几帧
    int capacity;
    int whichDock;
};

struct box{
    int value;
    point position;
    int bornTime;//出现时间，第几帧
    box();
};

struct dock{
    const int threshold1 = 50;
    const int threshold2 = 20;

    int id;
    int vLoad;
    int vRobot;
    robots* robot;
    point position;
    int distances[MAP_SIZE_X][MAP_SIZE_Y];
    int counter;//物品数量
    dock();
    void calcVRobot();
};

struct robots{
    int id;
    int Dockid;
    dock* targetDock;
    point position;
    int status;//FETCH or RETURN or PENDING
    box targetBox;
    int boxBFS[MAP_SIZE_X][MAP_SIZE_Y];//目标箱子的bfs结果
    Direction next;
    bool pull;
    bool get;
    int modified;
    void initPerFrame(point p);
    void findBestBox(std::list<box>& boxes, int currentTime);
    void greedyGetNext();
    bool pullBox();
    bool getBox();
    void Reset();//以防箱子丢失
    void findCollision(robots others[], int size);
    void handleCollision(robots& other, int flag);
};
