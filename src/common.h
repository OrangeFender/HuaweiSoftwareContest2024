struct point {
    int x;
    int y;
    point(int x, int y);
    point moveAstep(int direction);
    point moveSteps(int direction, int len);
    int getDistance(point other);
    bool horizontal_or_vertical(point other);
};