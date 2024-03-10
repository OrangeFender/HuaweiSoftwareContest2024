#ifndef DEFS_H
#define DEFS_H

#define NUM_ROBOTS 10
#define NUM_BOATS 10
#define NUM_DOCKS 5
#define MAP_SIZE_X 200
#define MAP_SIZE_Y 200

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define ROTATE_LEFT(direction) \
    do { \
        switch (direction) { \
            case RIGHT: \
                direction = UP; \
                break; \
            case LEFT: \
                direction = DOWN; \
                break; \
            case UP: \
                direction = LEFT; \
                break; \
            case DOWN: \
                direction = RIGHT; \
                break; \
        } \
    } while (0)

#define ROTATE_RIGHT(direction) \
    do { \
        switch (direction) { \
            case RIGHT: \
                direction = DOWN; \
                break; \
            case LEFT: \
                direction = UP; \
                break; \
            case UP: \
                direction = RIGHT; \
                break; \
            case DOWN: \
                direction = LEFT; \
                break; \
        } \
    } while (0)


#endif // DEFS_H