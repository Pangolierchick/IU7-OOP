#pragma once

enum MoveDirection {
    DOWN,
    NONE,
    UP,
};

enum LiftTimes {
    LIFT_MOVING_TIME = 1500,
    DOORS_MOVING_TIME = 2000,
    LIFT_WAIT_TIME = 2000,
};

#define FLOORS_NUM 10
#define START_POS 1
