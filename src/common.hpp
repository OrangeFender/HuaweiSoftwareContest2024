#include<cmath>

struct point {
    int x;
    int y;
    point(int x = -1 , int y = -1);
    point moveOneStep(int direction);
    point moveSteps(int direction, int len);
    int getDistance(const point& other);
    bool isHorizontalOrVertical(const point& other);
    bool valid();
    template <typename T>
    T getMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y]);
    template <typename T>
    void setMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y], T value);
};