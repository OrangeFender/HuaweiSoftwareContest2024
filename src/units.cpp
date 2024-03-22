#include"units.hpp"
#include"common.hpp"
//#include<iostream>



box::box(){
    
}

box::box(point p, int v, int time){
    position = p;
    value = v;
    bornTime = time;
}




bool compareT(const dock& a, const dock& b)
{
    return a.vRobot > b.vRobot;  // 使用 ">" 运算符实现降序排序
}

void boat_bind_dock(boat* boat_arr, dock* dock_arr)
{

    std::vector<dock> dock_vector(dock_arr, dock_arr + NUM_DOCKS);
    sort(dock_vector.begin(), dock_vector.end(), compareT); // 降序排序

    for (int i = 0; i < NUM_BOATS; i++)
    {
        boat_arr[i].whichDock1 = dock_vector[i].id;
        boat_arr[i].whichDock2 = dock_vector[NUM_DOCKS - 1 - i].id;
    }
}

//int boat::capacity = 0;

boat::boat() {
    setoffTime = 0;
    capacity = 0;
    id = 0;
    pos = -1;
    status = 1;
    goods_num = 0;
    operation = 0;
}

boat::boat(int SetTime, int dock1, int dock2, int ID, int Des, int Status, int Goods_num)
{
    setoffTime = SetTime;
    whichDock1 = dock1;
    whichDock2 = dock2;
    id = ID;
    pos = Des;
    status = Status;
    goods_num = Goods_num;
    operation = 0;
}

int boat::cal_arriveTime(dock dock1,dock dock2, int setoffTime, int pos)
{
    int arriveTime = setoffTime;

    switch (pos)
    {
    case 1: // 虚拟点到dock1
        arriveTime = setoffTime + dock1.transport_time;
        break;
    case 2: // dock1到dock2
        arriveTime = setoffTime + 500;
        break;
    case -1: // dock2去虚拟点
        arriveTime = setoffTime + dock2.transport_time;
        break;
    default:
        // 处理未知的pos值，这里可以选择抛出异常或进行默认处理
        break;
    }

    return arriveTime;
}

int boat::boat_ope(int sta, int dock_id,int time,dock& dock1,dock& dock2)
{
    //由于一艘船对应两个港口，所以不会出现在泊位外等待的情况，不用考虑boat_arr[i].status == 2的情况

    status = sta;
    if (dock_id == whichDock1)
        pos = 1;
    if (dock_id == whichDock2)
        pos = 2;
    if (dock_id == -1)
        pos = -1;
    if (status == BOAT_MOVING)  //如果移动中，就不需要对船进行操作
    {
        operation = BOAT_NONE;
        return BOAT_NONE;
    }
    if (status == BOAT_LOADING)  //如果正常运行状态
    {
        if (pos == -1)  //目标港口为-1，代表运输完成，那么返回港口1
        {
            goods_num = 0;
            pos = 1;
            setoffTime = time;
            operation = BOATGO_DOCK1;
            return BOATGO_DOCK1;
        }
        if (pos == 1)  //在港口1进行装货
        {
            if(goods_num >= capacity)  //货装满了，就去虚拟点
            {
                pos = -1;
                setoffTime = time;
                operation = BOATGO_VIRTUAL;
                return BOATGO_VIRTUAL;
            }
            if (dock1.counter == 0)  //港口1货装完了，就去港口2
            {
                pos = 2;
                setoffTime = time;
                operation = BOATGO_DOCK2;
                return BOATGO_DOCK2;
            }
            if (dock1.counter >= dock1.loading_speed)  //有货继续装
            {
                goods_num += dock1.loading_speed;
                dock1.counter-= dock1.loading_speed;
                if(goods_num > capacity)//装满了，剩余的货物放回去，去虚拟点
                {
                    dock1.counter += goods_num - capacity;
                    goods_num = capacity;
                    pos = -1;
                    setoffTime = time;
                    operation = BOATGO_VIRTUAL;
                    return BOATGO_VIRTUAL;
                }
                operation = BOAT_NONE;
                return BOAT_NONE;
            }
            if (dock1.counter < dock1.loading_speed && dock1.counter>0)
            {
                goods_num += dock1.counter;
                dock1.counter -= dock1.counter;
                if(goods_num > capacity)//装满了，剩余的货物放回去，去虚拟点
                {
                    dock1.counter += goods_num - capacity;
                    goods_num = capacity;
                    pos = -1;
                    setoffTime = time;
                    operation = BOATGO_VIRTUAL;
                    return BOATGO_VIRTUAL;
                }
                operation = BOAT_NONE;
                return BOAT_NONE;
            }

        }
        if (pos == 2)  //在港口2进行装货
        {
            if(goods_num >= capacity)  //货装满了，就去虚拟点
            {
                pos = -1;
                setoffTime = time;
                operation = BOATGO_VIRTUAL;
                return BOATGO_VIRTUAL;
            }
            if (dock2.counter == 0)  //港口2货装完了，就去虚拟点
            {
                pos = -1;
                setoffTime = time;
                operation = BOATGO_VIRTUAL;
                return BOATGO_VIRTUAL;
            }
            if (dock2.counter >= dock2.loading_speed)  //有货继续装
            {
                goods_num += dock2.loading_speed;
                dock2.counter -= dock2.loading_speed;
                if(goods_num > capacity)//装满了，剩余的货物放回去，去虚拟点
                {
                    dock2.counter += goods_num - capacity;
                    goods_num = capacity;
                    pos = -1;
                    setoffTime = time;
                    operation = BOATGO_VIRTUAL;
                    return BOATGO_VIRTUAL;
                }
                operation = BOAT_NONE;
                return BOAT_NONE;
            }
            if (dock2.counter < dock2.loading_speed && dock2.counter>0)
            {
                goods_num += dock2.counter;
                dock2.counter -= dock2.counter;
                if(goods_num > capacity)//装满了，剩余的货物放回去，去虚拟点
                {
                    dock2.counter += goods_num - capacity;
                    goods_num = capacity;
                    pos = -1;
                    setoffTime = time;
                    operation = BOATGO_VIRTUAL;
                    return BOATGO_VIRTUAL;
                }
                operation = BOAT_NONE;
                return BOAT_NONE;
            }
        }
    }
    return BOAT_NONE;
}


dock::dock(){
    RobotID = -1;
    counter = 0;
    counter_summary = 0;
    value_summary = 0;
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            distances[i][j] = INF;
        }
    }
}


void dock::calcVRobot(){
    vRobot = 0;
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            if(distances[i][j] != INF&&distances[i][j]!=0)
            vRobot += 10.0/distances[i][j];
        }
    }
}

void dock::setDistance(mapinfo& M){
    M.bfs(position, distances);
}

robot::robot(){
    status = RETURN;//初始状态为返回港口
    next = NONE;
    pull = false;
    get = false;
    modified = 0;
    haveBox = false;
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            boxBFS[i][j] = INF;
        }
    }
}

robot::robot(point p,int id){
    position = p;
    this->id = id;
    status = RETURN;
    next = NONE;
    pull = false;
    get = false;
    modified = 0;
    haveBox = false;

}

void robot::initPerFrame(bool have,point p){
    if(have!=haveBox){
        //std::cerr<<"haveBox error"<<std::endl;
    }
    position = p;
    next = NONE;
    modified = 0;
    pull = false;
    get = false;
}




void robot::findBestBox(std::list<box>& boxes, int currentTime,mapinfo &M) {
    if(haveBox){
        return;
    }
    box bestBox;
    int bestValue = -1;
    auto bestIt = boxes.end();
    bool flag = false;
    if(boxes.empty()){
        status = PENDING;
        haveBox = false;
        return;
    }
    for (auto it = boxes.begin(); it != boxes.end(); ) {
        if (currentTime - it->bornTime > BOX_LIFE) {//如果箱子已经存在超过一定时间
            // if (it == bestIt) {
            //     bestIt = boxes.end();
            // }
            it = boxes.erase(it);
        } else {
            int value = (it->value) * 64 / (it->position.getMapValue(targetDock->distances)+bias); // 价值/距离
            if (value > bestValue) {
                bestValue = value;
                bestBox = *it;
                bestIt = it;
                flag = true;
            }
            ++it;
        }
    }
    if (flag) {
        boxes.erase(bestIt);
        targetBox = bestBox;
        for(int i = 0; i < MAP_SIZE_X; i++){
            for(int j = 0; j < MAP_SIZE_Y; j++){
                boxBFS[i][j] = INF;
            }
        }
        M.bfs(bestBox.position, boxBFS);
        status = FETCH;
    }
    
}

bool robot::pullBox() {
    if(position.getMapValue((targetDock->distances)) > 6){
        return false;
    }
    if(status==RETURN){
        int dx = position.x-targetDock->position.x;
        int dy = position.y-targetDock->position.y;
        if(dx >= 0 && dx <= 3 && dy >= 0 && dy <= 3){
            targetDock->counter++;
            targetDock->counter_summary++;
            targetDock->value_summary += targetBox.value;
            status = PENDING;
            if(haveBox){
                haveBox = false;
                pull = true;
                return true;
            }
            pull = false;
            return false;
        }
    }
    return false;
}

bool robot::getBox() {
    if(haveBox)return false;
    if(status==FETCH){
        if(position==targetBox.position){
            get = true;
            status = RETURN;
            haveBox = true;
            return true;
        }
    }
    return false;
}

void robot::greedyGetNext() {
    
    //if (position == targetBox.position) {
    //    next = NONE;
    //}
    
    Direction trys[2][4] = {{UP, LEFT, DOWN, RIGHT},{RIGHT, DOWN, LEFT, UP}};
    int random = rand()%2;

    if(status == FETCH){
        int old = position.getMapValue(boxBFS);
        for(int i = 0; i < 4; i++){
            if(position.moveOneStep(trys[random][i]).valid()){
                if(position.moveOneStep(trys[random][i]).getMapValue(boxBFS) < old){
                    next = trys[random][i];
                    return;
                }
            }
        }
    }
    if(status == RETURN){
        int old = position.getMapValue(targetDock->distances);
        for(int i = 0; i < 4; i++){
            if(position.moveOneStep(trys[random][i]).valid()){
                if(position.moveOneStep(trys[random][i]).getMapValue(targetDock->distances) < old){
                    next = trys[random][i];
                    return;
                }
            }
        }
    }
}

void robot::handleCollision(robot& other, int flag){//other 是被让的
    modified +=1;
    Direction trys[5] = {UP, LEFT, DOWN, RIGHT, NONE};
    int otherdistances[5];
    if(other.status == FETCH){
        for(int i = 0; i < 5; i++){
            otherdistances[i] = other.position.moveOneStep(trys[i]).getMapValue(other.boxBFS);
        }
    }
    else{
        for(int i = 0; i < 5; i++){
            otherdistances[i] = other.position.moveOneStep(trys[i]).getMapValue(other.targetDock->distances);
        }
    }
    Direction bestdir;
    int best = 0;
    if(flag == 2){
        for(int i = 0; i < 5; i++){
            if(trys[i]==next)continue;
            if(otherdistances[i] > best && otherdistances[i] < INF){
                best = otherdistances[i];
                bestdir = trys[i];
            }
        }
    }
    if(flag == 1){
        for(int i = 0; i < 5; i++){
            if(trys[i]==next||trys[i]==NONE)continue;
            if(otherdistances[i] > best && otherdistances[i] < INF){
                best = otherdistances[i];
                bestdir = trys[i];
            }
        }
    }
    next = bestdir;

}

void robot::findCollision(robot others[], int size){
    for (int i = 0; i < size; i++) {
        robot& other = others[i];
        if(id == other.id){
            continue;
        }
        if(position.getDistance(other.position) > 3){
            continue;
        }
        if(position.moveOneStep(next) == other.position.moveOneStep(other.next)){
            if(modified > other.modified){//如果自己已经让过了，就不让了
                other.handleCollision(*this, 2);
                other.findCollision(others, size);
            }
            else if(other.modified < modified){
                handleCollision(other, 2);
                findCollision(others, size);
            }
            else if(id < other.id){//id大的让
                other.handleCollision(*this, 2);
                other.findCollision(others, size);
            }
            else{
                handleCollision(other, 2);
                findCollision(others, size);
            }
        }
        else if(position.moveOneStep(next) == other.position && position == other.position.moveOneStep(other.next)){
            if(modified > other.modified){//如果自己已经让过了，就不让了
                other.handleCollision(*this, 1);
                other.findCollision(others, size);
            }
            else if(other.modified < modified){
                handleCollision(other, 1);
                findCollision(others, size);
            }
            else if(id < other.id){//id大的让
                other.handleCollision(*this, 1);
                other.findCollision(others, size);
            }
            else{
                handleCollision(other, 1);
                findCollision(others, size);
            }
        }
    }
}


bool robot::Collision(robot others[], int size,bool vec[NUM_ROBOTS]){
    bool flag = false;
    for (int i = 0; i < size; i++) {
        robot& other = others[i];
        if(id == other.id){
            continue;
        }
        if(position.getDistance(other.position) > 3){
            continue;
        }
        if(position.moveOneStep(next) == other.position.moveOneStep(other.next)||(position.moveOneStep(next) == other.position && position == other.position.moveOneStep(other.next))){
            flag = true;
            vec[id] = true;
            vec[other.id] = true;
        }
    }
    return flag;
}

void robot::RandomMove(mapinfo M){
    Direction trys[4] = {UP, LEFT, DOWN, RIGHT};
    while (true)
    {
        Direction Next = trys[rand()%4];
        if(position.moveOneStep(Next).valid()&&position.moveOneStep(Next).getMapValue(M.clearing)){
            next = Next;
            break;
        }
    }
}


void robot::findBestDock(dock docks[], int size){
    int best = INF;
    dock* bestDock = nullptr;
    for(int i = 0; i < size; i++){
        if(docks[i].RobotID != -1)continue;
        if(position.getMapValue(docks[i].distances) < best){
            best = position.getMapValue(docks[i].distances);
            bestDock = &docks[i];
        }
        //if(position.getMapValue(docks[i].distances) == INF){
        //    targetDock = nullptr;
        //    return;
        //}
    }
    targetDock = bestDock;
    if(targetDock != nullptr)
        bestDock->RobotID = id;
}