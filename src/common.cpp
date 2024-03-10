#include"defs.h"
#include"common.h"
#include<cmath>

point::point(int x, int y) : x(x), y(y) {}

point point::moveAstep(int direction) {
    switch (direction) {
    case RIGHT:
        return point(x, y + 1);
    case LEFT:
        return point(x, y + 1 );
    case UP:
        return point(x - 1, y);
    case DOWN:
        return point(x + 1, y);
    default:
        return point(x, y);
    }
}

point point::moveSteps(int direction, int len) {
    switch (direction) {
    case RIGHT:
        return point(x, y + len);
    case LEFT:
        return point(x, y - len);
    case UP:
        return point(x - len, y);
    case DOWN:
        return point(x + len, y);
    default:
        return point(x, y);
    }
}

int point::getDistance(point other) {
    return abs(x - other.x) + abs(y - other.y);
}

bool point::horizontal_or_vertical(point other) {
    return x == other.x || y == other.y;
}