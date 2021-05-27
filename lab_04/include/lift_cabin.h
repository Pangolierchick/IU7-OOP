#pragma once

#include "defines.h"
#include "lift_doors.h"
#include <QObject>
#include <QTimer>

class LiftCabin : public QObject {
    Q_OBJECT

    enum CabinState {
        MOVING,
        WAITING,
        STOPPED,
    };

public:
    explicit LiftCabin(QObject* parent = nullptr);

signals:
    void cabinCalled();

    void cabinStopped(int floor);
    void cabinMovingTo(int floor);
    void cabinReachedFloor(int floor);

public slots:
    void cabinMove();
    void cabinStop();
    void cabinCall(int floor);

private:
    int __curr_floor;
    int __target_floor;
    bool __new_target;

    CabinState __state;
    MoveDirection __direction;
    LiftDoors __doors;
    QTimer __floor_move_timer;
};
