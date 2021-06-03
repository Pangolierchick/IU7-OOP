#include "lift_controller.h"
#include <qdebug>

LiftController::LiftController(QObject* parent) : QObject(parent),
                                                  __curr_floor(START_POS),
                                                  __curr_target(START_STATE),
                                                  __target_map(FLOORS_NUM, false),
                                                  __state(PENDING),
                                                  __direction(NONE) {
    QObject::connect(this, SIGNAL(controllerStopped()), this, SLOT(stop()));
    QObject::connect(this, SIGNAL(searchTarget(int)), this, SLOT(set(int)));
}

bool LiftController::nextTarget(int& floor) {
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

    if (!is_found) {
        emit controllerStopped();
    }

    return is_found;
}


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

void LiftController::run(int floor) {
    if (__state == RUNNING) {
        __curr_floor = floor;
        __target_map[floor - 1] = false;

        __state = SEARCHING;

        emit searchTarget(floor);
    }
}

void LiftController::stop() {
    if (__state == RUNNING)
        __state = PENDING;
    
    if (__state == SEARCHING)
        __state = PENDING;
}

void LiftController::set(int floor) {
    if (__state == SEARCHING) {
        if (nextTarget(floor)) {
            __direction = (__curr_floor < __curr_target) ? UP : DOWN;
            __state = RUNNING;

            emit setTarget(floor);
        }
    }
}
