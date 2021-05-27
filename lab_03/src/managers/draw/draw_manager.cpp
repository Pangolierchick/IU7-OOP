#include "managers/draw/draw_manager.h"

#include <object/camera/camera.h>
#include <object/model/model.h>

void DrawManager::visit(const Model& model) {
    auto points = model._details->get_points();
    auto center = model._details->get_center();
    Point point_1, point_2;

    for (auto edge : model._details->get_edges()) {
        point_1 = point_proection(points.at(edge.get_first()).relative_to(center));
        point_2 = point_proection(points.at(edge.get_second()).relative_to(center));
        _drawer->draw_line(point_1, point_2);
    }
}

void DrawManager::visit(const Camera& camera) {}

void DrawManager::visit(const Composite& composite) {}

void DrawManager::set_drawer(std::shared_ptr<AbstractDrawer> drawer) {
    _drawer = std::move(drawer);
}

void DrawManager::set_camera(std::shared_ptr<Camera> new_camera) {
    _camera = std::move(new_camera);
}

Point DrawManager::point_proection(const Point& point) {
    Point new_point(point);
    Point camera_position(_camera->current_position);

    new_point.set_x(new_point.get_x() + camera_position.get_x());
    new_point.set_y(new_point.get_y() + camera_position.get_y());

    return new_point;
}
