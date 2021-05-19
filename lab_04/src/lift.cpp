#include "lift.h"

Lift::Lift() {
    QObject::connect(&__controller, SIGNAL(setTarget(int)), &__cabin, SLOT(cabinCall(int)));
    QObject::connect(&__cabin, SIGNAL(cabinMovingTo(int)), &__controller, SLOT(traversedFloor(int)));
    QObject::connect(&__cabin, SIGNAL(cabinStopped(int)), &__controller, SLOT(reachedFloor(int)));
}

void Lift::call(int floor) {
    __controller.newTarget(floor);
}
