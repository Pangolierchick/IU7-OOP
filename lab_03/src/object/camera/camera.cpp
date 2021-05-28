#include "object/camera/camera.h"

void Camera::transform(const Point& new_position, const Point& scale, const Point& rotate) {
    move_x(new_position.get_x());
    move_y(new_position.get_y());
}

void Camera::accept(std::shared_ptr<Visitor> visitor) {
    visitor->visit(*this);
}

void Camera::move_x(const double& change) {
    current_position.set_x(current_position.get_x() + change);
}

void Camera::move_y(const double& change) {
    current_position.set_y(current_position.get_y() + change);
}

void Camera::move_z(const double& change) {
    current_position.set_z(current_position.get_z() + change);
}
