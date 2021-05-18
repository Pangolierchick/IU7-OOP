#pragma once

#include <QObject>

class LiftController : public QObject {
    Q_OBJECT

    public:
        explicit LiftController(QObject *parent=nullptr);
        void newTarget(int floor);
    
    signals:
        void setTarget(int floor);
    
    public slots:
        void reachedFloor(int floor);
        void traversedFloor(int floor);
    
    private:
        int __cur_floor;
        int __curr_target = 0; //FIXME

        QVector<bool> __target_map;
        bool nextTarget(int floor);
        void findNewTarget();
};
