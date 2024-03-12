#include<cmath>


#define INF 1000000000

#define NUM_ROBOTS 10
#define NUM_BOATS 10
#define NUM_DOCKS 5
#define MAP_SIZE_X 200
#define MAP_SIZE_Y 200


enum Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

Direction rotateLeft(Direction direction);
Direction rotateRight(Direction direction);

struct point {
    int x;
    int y;
    point(int x = -1 , int y = -1);
    point moveOneStep(Direction direction);
    point moveSteps(Direction direction, int len);
    int getDistance(const point& other);
    bool isHorizontalOrVertical(const point& other);
    bool valid();
    template <typename T>
    T getMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y]);
    template <typename T>
    void setMapValue(T map[MAP_SIZE_X][MAP_SIZE_Y], T value);
};