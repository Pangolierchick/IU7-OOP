#pragma once

#include <QObject>
#include "lift_cabin.h"
#include "lift_controller.h"


class Lift : public QObject {
    public:
        Lift();
        void call(int floor);
    
    private:
        LiftController __controller;
        LiftCabin      __cabin;
};
