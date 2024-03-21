#include<cmath>

#pragma once

#define INF 1000000000

#define NUM_ROBOTS 10
#define NUM_BOATS 5
#define NUM_DOCKS 10
#define MAP_SIZE_X 200
#define MAP_SIZE_Y 200

#define BOX_LIFE 1000



enum Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};

Direction rotateLeft(Direction direction);
Direction rotateRight(Direction direction);

struct point {
    int x;
    int y;
    point(int x = -1 , int y = -1);
    point moveOneStep(Direction direction) const;//移动一个单位
    point moveSteps(Direction direction, int len) const;//移动多个单位
    int getDistance(const point& other);
    bool isHorizontalOrVertical(const point& other);
    bool valid();
    template <typename T>
    T getMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y]);//读取二维数组的值
    template <typename T>
    void setMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y], T value);//设置二维数组的值
    bool operator==(const point& other);
};