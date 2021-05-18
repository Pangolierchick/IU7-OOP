#pragma once

#include <QObject>

class LiftCabin : public QObject {
    Q_OBJECT

    public:
        explicit LiftCabin(QObject *parent = nullptr);

    signals:
        void cabinCalled();
        void cabinStopped();

        void cabinMovingTo(int floor);
        void cabinReachedFloor(int floor);
    
    public slots:
        void cabinMove();
        void cabinStop();
        void cabinCall(int floor);
    
    private:
        int  __curr_floor;
        int  __target_floor;
        bool __new_target;
        //TODO
};
