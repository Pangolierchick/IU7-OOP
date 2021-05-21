#pragma once

#include <QObject>
#include <QTimer>

class LiftDoors : public QObject {
    Q_OBJECT

    enum DoorState {
        OPEN,
        CLOSED,
        OPENNING,
        CLOSING
    };

public:
    explicit LiftDoors(QObject* parent = nullptr);

signals:
    void closedDoors();
    void openedDoors();

public slots:
    void openning();
    void closing();

private slots:
    void open();
    void close();

private:
    DoorState __state;
    QTimer __open_timer;
    QTimer __close_timer;
    QTimer __wait_timer;
};
 