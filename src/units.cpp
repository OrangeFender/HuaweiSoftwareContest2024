#include"units.hpp"
#include"common.hpp"

box::box(){
    
}

boat::boat(){
    //刘志
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
            if(distances[i][j] < threshold1){
                vRobot++;
            }
            if(distances[i][j] < threshold2){
                vRobot++;
            }
        }
    }
}

void dock::setDistance(mapinfo& M){
    M.bfs(position, distances);
}

robot::robot(){
    status = PENDING;
    next = NONE;
    pull = false;
    get = false;
    modified = 0;
}

robot::robot(point p,int id){
    position = p;
    this->id = id;
    status = PENDING;
    next = NONE;
    pull = false;
    get = false;
    modified = 0;

}

void robot::initPerFrame(point p){
    position = p;
    next = NONE;
    modified = 0;
    pull = false;
    get = false;
}


void robot::findBestBox(std::list<box>& boxes, int currentTime) {
    box bestBox;
    int bestValue = -1;
    auto bestIt = boxes.end();
    for (auto it = boxes.begin(); it != boxes.end(); ) {
        if (currentTime - it->bornTime > BOX_LIFE) {
            if (it == bestIt) {
                bestIt = boxes.end();
            }
            it = boxes.erase(it);
        } else {
            int value = (it->value) * 64 / (it->position.getMapValue(targetDock->distances)+bias); // 价值/距离
            if (value > bestValue) {
                bestValue = value;
                bestBox = *it;
                bestIt = it;
            }
            ++it;
        }
    }
    if (bestIt != boxes.end()) {
        boxes.erase(bestIt);
    }
    targetBox = bestBox;
}

bool robot::pullBox() {
    if(position.getMapValue((targetDock->distances)) > 6){
        return false;
    }
    if(status==RETURN){
        int dx = targetDock->position.x - position.x;
        int dy = targetDock->position.y - position.y;
        if(dx >= 0 && dx <= 3 && dy >= 0 && dy <= 3){
            targetDock->counter++;
            targetDock->counter_summary++;
            targetDock->value_summary += targetBox.value;
            pull = true;
            return true;
        }
    }
    return false;
}

bool robot::getBox() {
    if(status==FETCH){
        if(position==targetBox.position){
            get = true;
            return true;
        }
    }
    return false;
}

void robot::greedyGetNext() {
    if (position == targetBox.position) {
        next = NONE;
    }
    
    Direction trys[4] = {UP, LEFT, DOWN, RIGHT};
    int old = position.getMapValue(boxBFS);
    for(int i = 0; i < 4; i++){
        if(position.moveOneStep(trys[i]).valid()){
            if(position.moveOneStep(trys[i]).getMapValue(boxBFS) < old){
                next = trys[i];
                return;
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
        if(position.getDistance(other.position) > 2){
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

void robot::findBestDock(dock docks[], int size){
    int best = INF;
    dock* bestDock = nullptr;
    for(int i = 0; i < size; i++){
        if(docks[i].RobotID != -1)continue;
        if(position.getMapValue(docks[i].distances) < best){
            best = position.getMapValue(docks[i].distances);
            bestDock = &docks[i];
        }
    }
    targetDock = bestDock;
    bestDock->RobotID = id;
}