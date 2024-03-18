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