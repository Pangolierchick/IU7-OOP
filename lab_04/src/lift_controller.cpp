#include <qdebug>
#include "lift_controller.h"

LiftController::LiftController(QObject *parent) : QObject(parent), 
                                                  __curr_floor(START_POS), 
                                                  __curr_target(START_STATE),
                                                  __target_map(FLOORS_NUM, false),
                                                  __state(PENDING),
                                                  __direction(NONE) {}


void LiftController::newTarget(int floor) {
    __state = RUNNING;
    __target_map[floor - 1] = true;

    if (__curr_target == START_STATE) {
        __curr_target = floor;
    }

    if ((__direction == UP && __curr_floor < floor) || (__direction == DOWN && __curr_floor > floor)) {
        __curr_target = floor;
    }

    if (__curr_floor < __curr_target)
        __direction = UP;
    else
        __direction = DOWN;
    
    emit setTarget(floor);
}

void LiftController::reachedFloor(int floor) {
    if (__state == RUNNING) {
        __curr_floor = floor;
        __target_map[floor - 1] = false;

        if (__curr_floor == __curr_target) {
            __curr_target = START_STATE;
            findNewTarget();
        }

        if (nextTarget(floor)) {
            __direction = (__curr_floor < __curr_target) ? UP : DOWN;

            emit setTarget(floor);
        } else {
            __state = PENDING;
        }
    }
}

void LiftController::traversedFloor(int floor) {
    __curr_floor = floor;
    qDebug() << "Moving. Floor #" << floor;
}

bool LiftController::nextTarget(int &floor) {
    bool is_found = false;
    bool first = true;

    if (__curr_floor > __curr_target) {
        for (int i = __curr_floor; i > 0 && first; i--) {
            if (__target_map[i - 1]) {
                first = false;
                is_found = true;
                floor = i;
            }
        }
    } else {
        for (int i = __curr_floor; i < FLOORS_NUM && first; i++) {
            if (__target_map[i - 1]) {
                first = false;
                is_found = true;
                floor = i;
            }
        }
    }

    return is_found; 
}

void LiftController::findNewTarget() {
    if (__direction == DOWN) {
        for (int i = FLOORS_NUM; i > 0; i--) {
            if (__target_map[i - 1]) {
                __curr_target = i;
            }
        }
    } else {
        for (int i = 1; i < FLOORS_NUM; i++) {
            if (__target_map[i - 1]) {
                __curr_target = i;
            }
        }
    }
}


