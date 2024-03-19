#include"units.hpp"
#include"common.hpp"

box::box(){
    
}

dock::dock(){
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            distances[i][j] = INF;
        }
    }
}

void robots::findBest(std::list<box>& boxes, int currentTime) {
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
            int value = (it->value) / static_cast<int>(it->position.getMapValue(targetDock->distances)); // 价值/距离
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

bool robots::pull() {
    if(position.getMapValue((targetDock->distances)) > 6){
        return false;
    }
    if(status==RETURN){
        int dx = targetDock->position.x - position.x;
        int dy = targetDock->position.y - position.y;
        if(dx >= 0 && dx <= 3 && dy >= 0 && dy <= 3){
            return true;
        }
    }
    return false;
}

bool robots::get() {
    if(status==FETCH){
        if(position==targetBox.position){
            return true;
        }
    }
    return false;
}

void robots::greedyGetNext() {
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

void robots::handleCollision(robots& other, int flag){//other 是被让的
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
            if(otherdistances[i] > best){
                best = otherdistances[i];
                bestdir = trys[i];
            }
        }
    }
    if(flag == 1){
        for(int i = 0; i < 5; i++){
            if(trys[i]==next||trys[i]==NONE)continue;
            if(otherdistances[i] > best){
                best = otherdistances[i];
                bestdir = trys[i];
            }
        }
    }
    next = bestdir;
}

void robots::findCollision(robots& other){
    if(id == other.id){
        return;
    }
    if(position.getDistance(other.position) > 2){
        return;
    }
    if(position.moveOneStep(next) == other.position.moveOneStep(other.next)){
        if(id < other.id){//id大的让
            other.handleCollision(*this, 2);
        }
        else{
            handleCollision(other, 2);
        }
    }
    else if(position.moveOneStep(next) == other.position && position == other.position.moveOneStep(other.next)){
        if(id < other.id){
            other.handleCollision(*this, 1);
        }
        else{
            handleCollision(other, 1);
        }
    }
}




