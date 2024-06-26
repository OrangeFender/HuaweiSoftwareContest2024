#include"common.hpp"
#include"map.hpp"
#include<list>
#include <algorithm>
#include <vector>


//关于机器人的状态
#define FETCH 0 //去拿箱子
#define RETURN 1 //去送箱子
#define PENDING 2 //未指定箱子

//0:不操作 1:去港口1 2:去港口2 3:去虚拟点
#define BOAT_NONE 0
#define BOATGO_DOCK1 1
#define BOATGO_DOCK2 2
#define BOATGO_VIRTUAL 3

#define BOAT_MOVING 0
#define BOAT_LOADING 1

#define loadingTime 10
#define kazhenTime 5

// struct boat{
//     int setoffTime;//出发时间，第几帧
//     int arriveTime;//到达时间，第几帧
//     static int capacity;
//     int whichDock;
    
//     boat();
// };

struct dock;

struct boat {
    int setoffTime;//出发时间，第几帧
    int seperateTime;
    int lastTime;
    //int arriveTime;//到达时间，第几帧
    static int capacity;//船的容量
    int whichDock1;//虚拟点到dock1  0-9
    int whichDock2;//dock2到虚拟点
    int id;//船的标号1-5
    int pos;//船当前的目的地  1代表去dock1，2代表去dock2，-1代表去虚拟点
    int status;//船当前的状态
    int goods_num;//当前装载的货物量
    int operation;//当前操作
    int flag;//0代表未拾取第二阶段的dock1  1代表已经拾取了dock1
    boat();
    boat(int SetTime, int dock1, int dock2, int ID, int Des, int Status, int Goods_num);
    int cal_seperateTime(dock dock1,dock dock2);
    int cal_lastTime(dock dock1,dock dock2);//dock1运输时间长，dock2运输时间短
    int cal_arriveTime(dock dock1,dock dock2,int setoffTime, int pos);
    int boat_ope(int sta, int dock_id,int time,dock& dock1,dock& dock2);//返回值 0:不操作 1:去港口1 2:去港口2 3:去虚拟点
    
};


struct box{
    int value;
    point position;
    int bornTime;//出现时间，第几帧
    box();
    box(point p, int val, int time);
};


struct dock{
    int threshold1 {50};
    int threshold2 {20};

    int id;
    int transport_time;//到虚拟点的时间
    int loading_speed;//装箱速度
    double vRobot;//机器人的效率（空旷程度）
    int RobotID;//对应的机器人ID
    point position;//左上角坐标
    int distances[MAP_SIZE_X][MAP_SIZE_Y];//到每个点的距离，用BFS计算
    int counter;//当前物品数量
    int counter_summary;//记录物品总数目
    int value_summary;//记录物品总价值
    bool isBind;//是否被绑定
    dock* friendDock;//对应的另一个码头
    dock();
    dock(mapinfo& M, point p, int id,int Load);//初始化码头位置和每个点的距离
    void calcVRobot();//计算机器人的效率
    void setDistance(mapinfo& M);//BFS
};


void boat_bind_dock(boat* boat_arr, dock* dock_arr);


struct robot{
    const int bias = 10;//越大越倾向于价值大的箱子
    int id;
    int Dockid;//对应的码头ID
    dock* targetDock;//目标码头指针
    point position;//当前位置
    int status;//FETCH or RETURN or PENDING
    box targetBox;//目标箱子
    int boxBFS[MAP_SIZE_X][MAP_SIZE_Y];//目标箱子的bfs结果
    Direction next;//下一步的方向
    bool pull;//放箱子
    bool get;//拿箱子
    int modified;//是否被修改过
    bool haveBox;//是否有箱子
    bool blacklisted[5];//是否被列入黑名单
    bool changed;//是否被改变过
    robot();
    robot(point p,int id);
    void initPerFrame(bool have,point p);
    void greedyGetNext();//计算下一步的方向
    bool pullBox();//放箱子
    bool getBox();//拿箱子
    void Reset();//以防箱子丢失
    void findBestBox(std::list<box>& boxes, int currentTime,mapinfo &M);
    void findBestBox(robot others[],std::list<box>& boxes, int currentTime,mapinfo &M);
    void findCollision(robot others[], int size);//
    void handleCollision(robot& other, int flag);
    bool Collision(robot others[], int size,bool vec[NUM_ROBOTS]);//判断是否会发生碰撞
    bool narrowCollision(point p,Direction from,robot others[], int size,mapinfo M);//判断是否会发生碰撞
    void RandomMove(mapinfo);//随机移动
    void findBestDock(dock docks[], int size);//初始阶段，找到最优的码头
};
