#include "lift_doors.h"
#include "defines.h"
#include <qdebug>

LiftDoors::LiftDoors(QObject* parent) : QObject(parent), __state(CLOSED) {
    __open_timer.setSingleShot(true);
    __close_timer.setSingleShot(true);

    QObject::connect(&__open_timer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(&__close_timer, SIGNAL(timeout()), this, SLOT(close()));

    __wait_timer.setInterval(LIFT_WAIT_TIME);
    __wait_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(openedDoors()), &__wait_timer, SLOT(start()));
    QObject::connect(&__wait_timer, SIGNAL(timeout()), this, SLOT(closing()));
}

void LiftDoors::openning() {
    if (__state == CLOSED) {
        qDebug() << "Doors are openning.";

        __state = OPENNING;
        __open_timer.start(DOORS_MOVING_TIME);
    }
}

void LiftDoors::closing() {
    if (__state == OPEN) {
        qDebug() << "Doors are closing.";

        __state = CLOSING;
        __close_timer.start(DOORS_MOVING_TIME);
    } else if (__state == CLOSED) {
        emit closedDoors();
    }
}

void LiftDoors::close() {
    if (__state == CLOSING) {
        qDebug() << "Doors are closed.";

        __state = CLOSED;

        emit closedDoors();
    }
}

void LiftDoors::open() {
    if (__state == OPENNING) {
        qDebug() << "Doors are open.";

        __state = OPEN;

        emit openedDoors();
    }
}
