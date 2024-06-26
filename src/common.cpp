#include"common.hpp"

Direction rotateLeft(Direction direction) {
    switch (direction) {
        case RIGHT:
            return UP;
        case LEFT:
            return DOWN;
        case UP:
            return LEFT;
        case DOWN:
            return RIGHT;
    }
    return direction;
}

Direction rotateRight(Direction direction) {
    switch (direction) {
        case RIGHT:
            return DOWN;
        case LEFT:
            return UP;
        case UP:
            return RIGHT;
        case DOWN:
            return LEFT;
    }
    return direction;
}

Direction opposite(Direction direction) {
    switch (direction) {
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
        case UP:
            return DOWN;
        case DOWN:
            return UP;
    }
    return direction;
}


point::point(int x, int y) : x(x), y(y) {}

point point::moveOneStep(Direction direction) const {
    switch (direction) {
    case RIGHT:
        return point(x, y + 1);
    case LEFT:
        return point(x, y - 1 );
    case UP:
        return point(x - 1, y);
    case DOWN:
        return point(x + 1, y);
    default:
        return point(x, y);
    }
}

point point::moveSteps(Direction direction, int len) const {
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

int point::getDistance(const point& other) {
    return abs(x - other.x) + abs(y - other.y);
}

bool point::isHorizontalOrVertical(const point& other) {
    return x == other.x || y == other.y;
}

bool point::valid() {
    return x >= 0 && x < MAP_SIZE_X && y >= 0 && y < MAP_SIZE_Y;
}

bool point::operator==(const point& other) {
    return x == other.x && y == other.y;
}