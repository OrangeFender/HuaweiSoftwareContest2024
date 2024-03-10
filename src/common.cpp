#include"defs.h"
#include"common.h"

point::point(int x, int y) : x(x), y(y) {}

point point::moveAstep(int direction) {
    switch (direction) {
    case RIGHT:
        return point(x, y + 1);
    case LEFT:
        return point(x, y + 1 );
    case UP:
        return point(x + 1, y);
    case DOWN:
        return point(x - 1, y);
    default:
        return point(x, y);
    }
}

