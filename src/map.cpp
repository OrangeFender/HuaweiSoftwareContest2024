#include "map.hpp"


void mapinfo::dfs(point src, int distance, int distances[MAP_SIZE_X][MAP_SIZE_Y]) {
    // Check if the current position is within the map boundaries
    if (!src.valid()) {
        return;
    }
    // Check if the current position is a wall or already visited
    if (!src.getMapValue(clearing) || distance >= src.getMapValue(distances)) {
        return;
    }
    // if the current distance is smaller than the previously recorded distance
    src.setMapValue(distances, distance);
    // Move to the adjacent positions (up, down, left, right)
    dfs(src.moveOneStep(UP), distance + 1, distances);
    dfs(src.moveOneStep(DOWN), distance + 1, distances);
    dfs(src.moveOneStep(LEFT), distance + 1, distances);
    dfs(src.moveOneStep(RIGHT), distance + 1, distances);
}

//从码头到每个点的最短距离
void mapinfo::bfs(point src,int distances[MAP_SIZE_X][MAP_SIZE_Y]){
    std::vector<point> queue;
    queue.push_back(src);
    src.setMapValue(distances, 0);
    while(!queue.empty()){
        point p = queue[0];
        queue.erase(queue.begin());
        Direction directions[] = {UP, DOWN, LEFT, RIGHT};
        for (int i = 0; i < 4; i++) {
            Direction dir = directions[i];
            point nextPoint = p.moveOneStep(dir);
            if(nextPoint.valid())break;
            if(nextPoint.getMapValue(clearing) && nextPoint.getMapValue(distances) == INF){
                nextPoint.setMapValue(distances, p.getMapValue(distances) + 1);
                queue.push_back(nextPoint);
            }
        }
    }
}

mapinfo::mapinfo(char map[MAP_SIZE_X][MAP_SIZE_Y]){
    int count = 0;
    bool flag = false;
    for (int i = 0; i <= MAP_SIZE_X - 4; i++) {
        if(flag) break;
        for (int j = 0; j <= MAP_SIZE_Y - 4; j++) {
            if (map[i][j] == 'B' && map[i][j + 1] == 'B' && map[i][j + 2] == 'B' && map[i][j + 3] == 'B' &&
                map[i + 1][j] == 'B' && map[i + 1][j + 1] == 'B' && map[i + 1][j + 2] == 'B' && map[i + 1][j + 3] == 'B' &&
                map[i + 2][j] == 'B' && map[i + 2][j + 1] == 'B' && map[i + 2][j + 2] == 'B' && map[i + 2][j + 3] == 'B' &&
                map[i + 3][j] == 'B' && map[i + 3][j + 1] == 'B' && map[i + 3][j + 2] == 'B' && map[i + 3][j + 3] == 'B') {
                // Record the minimum vertex index
                int minX = i;
                int minY = j;
                docks[count].position = point(minX, minY);
                count++;
            }
            if(count == NUM_DOCKS){
                flag = true;
                break;
            }
        }
    }
    // count will contain the total number of 4x4 squares with 'B' in the map

    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            if(map[i][j] == 'B' || map[i][j] == 'A'|| map[i][j] == '.')//可以通过
                clearing[i][j] = true;
            else
                clearing[i][j] = false;
        }
    }
}