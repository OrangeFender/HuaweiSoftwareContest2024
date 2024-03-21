#include"common.hpp"
#include"map.hpp"
//关于机器人的状态
#define FETCH 0
#define RETURN 1
#define PENDING 2

#include<list>

#define BOAT_BACK 0
#define BOAT_GO 1
#define BOAT_LOADING 2

struct boat{
    int setoffTime;//出发时间，第几帧
    static int capacity;
    int whichDock;
    int status;
    boat();
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
    int transport_time;
    int loading_speed;
    int vRobot;
    int RobotID;
    point position;
    int distances[MAP_SIZE_X][MAP_SIZE_Y];
    int counter;//物品数量
    dock();
    dock(mapinfo& M, point p, int id,int Load);//初始化码头位置和每个点的距离
    void calcVRobot();
};

struct robot{
    const int bias = 5;//越大越倾向于价值大的箱子
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
    robot();
    robot(point p,int id);
    void initPerFrame(point p);
    void findBestBox(std::list<box>& boxes, int currentTime);
    void greedyGetNext();
    bool pullBox();
    bool getBox();
    void Reset();//以防箱子丢失
    void findCollision(robot others[], int size);
    void handleCollision(robot& other, int flag);
    void findBestDock(dock docks[], int size);
};
