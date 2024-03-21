#include"common.hpp"
#include"map.hpp"
//关于机器人的状态
#define FETCH 0
#define RETURN 1
#define PENDING 2

#include<list>



struct boat{
    int setoffTime;//出发时间，第几帧
    int arriveTime;//到达时间，第几帧
    static int capacity;
    int whichDock;
    
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
    int transport_time;//到虚拟点的时间
    int loading_speed;
    int vRobot;
    int RobotID;
    point position;
    int distances[MAP_SIZE_X][MAP_SIZE_Y];
    int counter;//当前物品数量
    int counter_summary;//记录物品总数目
    int value_summary;//记录物品总价值
    dock();
    dock(mapinfo& M, point p, int id,int Load);//初始化码头位置和每个点的距离
    void calcVRobot();
    void setDistance(mapinfo& M);
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
    void greedyGetNext();//计算下一步的方向
    bool pullBox();//放箱子
    bool getBox();//拿箱子
    void Reset();//以防箱子丢失
    void findCollision(robot others[], int size);
    void handleCollision(robot& other, int flag);
    void findBestDock(dock docks[], int size);
};
