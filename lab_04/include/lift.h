#pragma once

#include "lift_cabin.h"
#include "lift_controller.h"
#include <QObject>

class Lift : public QObject {
public:
    Lift();
    void call(int floor);

private:
    LiftController __controller;
    LiftCabin __cabin;
};
