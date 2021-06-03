#pragma once

#include "defines.h"
#include <QObject>

class LiftController : public QObject {
    Q_OBJECT

    enum ControllerState {
        RUNNING,
        SEARCHING,
        PENDING,
    };

public:
    explicit LiftController(QObject* parent = nullptr);
    void newTarget(int floor);

signals:
    void setTarget(int floor);
    void controllerStopped();
    void searchTarget(int floor);

public slots:
    void run(int floor);
    void stop();
    void set(int floor);

private:
    int __curr_floor;
    int __curr_target = 0;

    QVector<bool>   __target_map;
    ControllerState __state;
    MoveDirection   __direction;

    bool nextTarget(int& floor);
};
