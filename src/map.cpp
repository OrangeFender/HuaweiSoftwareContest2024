#include "map.hpp"

#include<vector>

void mapinfo::dfs(point p, int dockIndex, int distance ) {
    // Check if the current position is within the map boundaries
    if (!p.valid()) {
        return;
    }
    // Check if the current position is a wall or already visited
    if (!p.getMapValue(clearing) || distance >= p.getMapValue(distances[dockIndex])) {
        return;
    }
    // if the current distance is smaller than the previously recorded distance
    p.setMapValue(distances[dockIndex], distance);
    // Move to the adjacent positions (up, down, left, right)
    dfs(p.moveOneStep(UP), dockIndex, distance + 1);
    dfs(p.moveOneStep(DOWN), dockIndex, distance + 1);
    dfs(p.moveOneStep(LEFT), dockIndex, distance + 1);
    dfs(p.moveOneStep(RIGHT), dockIndex, distance + 1);
}

//从码头到每个点的最短距离
void mapinfo::bfs(int dockIndex){
    std::vector<point> queue;
    queue.push_back(dockpoint[dockIndex]);
    dockpoint[dockIndex].setMapValue(distances[dockIndex], 0);
    while(!queue.empty()){
        point p = queue[0];
        queue.erase(queue.begin());
        Direction directions[] = {UP, DOWN, LEFT, RIGHT};
        for (int i = 0; i < 4; i++) {
            Direction dir = directions[i];
            point nextPoint = p.moveOneStep(dir);
            if(nextPoint.valid() && nextPoint.getMapValue(clearing) && nextPoint.getMapValue(distances[dockIndex]) == INF){
                nextPoint.setMapValue(distances[dockIndex], p.getMapValue(distances[dockIndex]) + 1);
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
                dockpoint[count] = point(minX, minY);
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
    // Initialize distances array
    for(int i = 0; i < MAP_SIZE_X; i++){
        for(int j = 0; j < MAP_SIZE_Y; j++){
            for(int k = 0; k < NUM_DOCKS; k++){
                distances[i][j][k] = INF; // Set initial distance to infinity
            }
        }
    }

    // Perform DFS traversal to calculate shortest distances
    for(int k = 0; k < NUM_DOCKS; k++){
        dfs(dockpoint[k], k, 0);
    }
}

int mapinfo::getDistance(point p, int dockIndex){
    return p.getMapValue(distances[dockIndex]);
}