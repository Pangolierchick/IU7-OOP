#pragma once

#include "managers/draw/draw_manager.h"
#include "object/object.h"
#include "visitor.h"

class Camera : public InvisibleObject {
    friend Point DrawManager::point_proection(const Point& point);

public:
    Camera() = default;
    explicit Camera(const Point& position) : current_position(position){};

    ~Camera() override = default;

    void transform(const Point& new_position, const Point& scale, const Point& rotate) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

private:
    void move_x(const double& change);
    void move_y(const double& change);
    void move_z(const double& change);

protected:
    Point current_position;
};
