#include "managers/transform/transform_manager.h"

void TransformManager::transform_object(const std::shared_ptr<Object>& object, const Point& move, const Point& scale, const Point& rotate) {
    object->transform(move, scale, rotate);
}

void TransformManager::move_object(const std::shared_ptr<Object>& object, const double dx, const double dy, const double dz) {
    Point move(dx, dy, dz);
    Point scale(1, 1, 1);
    Point rotate(0, 0, 0);

    object->transform(move, scale, rotate);
}

void TransformManager::scale_object(const std::shared_ptr<Object>& object, const double kx, const double ky, const double kz) {
    Point move(0, 0, 0);
    Point scale(kx, ky, kz);
    Point rotate(0, 0, 0);

    object->transform(move, scale, rotate);
}

void TransformManager::rotate_object(const std::shared_ptr<Object>& object, const double ox, const double oy, const double oz) {
    Point move(0, 0, 0);
    Point scale(1, 1, 1);
    Point rotate(ox, oy, oz);

    object->transform(move, scale, rotate);
}