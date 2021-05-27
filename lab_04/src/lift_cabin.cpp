#include "lift_cabin.h"
#include <qdebug>

LiftCabin::LiftCabin(QObject* parent) : QObject(parent),
                                        __curr_floor(START_POS),
                                        __target_floor(START_STATE),
                                        __new_target(false),
                                        __state(STOPPED),
                                        __direction(NONE) {
    QObject::connect(this, SIGNAL(cabinCalled()), &__doors, SLOT(closing()));
    QObject::connect(this, SIGNAL(cabinReachedFloor(int)), this, SLOT(cabinStop()));
    QObject::connect(this, SIGNAL(cabinStopped(int)), &__doors, SLOT(openning()));

    QObject::connect(&__doors, SIGNAL(closedDoors()), this, SLOT(cabinMove()));

    __floor_move_timer.setSingleShot(true);

    QObject::connect(&__floor_move_timer, SIGNAL(timeout()), this, SLOT(cabinMove()));
}

void LiftCabin::cabinMove() {
    if (__new_target) {
        if (__state == WAITING) {
            __state = MOVING;

            if (__curr_floor == __target_floor) {
                emit cabinReachedFloor(__curr_floor);
            } else {
                __floor_move_timer.start(LIFT_MOVING_TIME);
            }
        } else if (__state == MOVING) {
            __curr_floor += __direction;

            if (__curr_floor == __target_floor) {
                emit cabinReachedFloor(__curr_floor);
            } else {
                emit cabinMovingTo(__curr_floor);
                __floor_move_timer.start(LIFT_MOVING_TIME);
            }
        }
    }
}

void LiftCabin::cabinStop() {
    if (__state == MOVING) {
        __state = STOPPED;

        qDebug() << "Lift stopped at #" << __curr_floor;

        emit cabinStopped(__curr_floor);
    }
}

void LiftCabin::cabinCall(int floor) {
    if (__state == STOPPED) {
        __new_target = true;
        __state = WAITING;
        __target_floor = floor;

        if (__target_floor > __curr_floor)
            __direction = UP;
        else if (__target_floor < __curr_floor)
            __direction = DOWN;
        else
            __direction = NONE;

        emit cabinCalled();
    }
}
