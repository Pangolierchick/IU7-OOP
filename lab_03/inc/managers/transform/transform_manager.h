#pragma once

#include "managers/base_manager.h"
#include "object/object.h"

class TransformManager : public BaseManager {
public:
    TransformManager() = default;
    TransformManager(const TransformManager&) = delete;
    TransformManager& operator=(const TransformManager&) = delete;

    ~TransformManager() = default;

    static void transform_object(const std::shared_ptr<Object>& object, const Point& move, const Point& scale, const Point& rotate);

    static void move_object(const std::shared_ptr<Object>& object, const double dx, const double dy, const double dz);
    static void scale_object(const std::shared_ptr<Object>& object, const double kx, const double ky, const double kz);
    static void rotate_object(const std::shared_ptr<Object>& object, const double ox, const double oy, const double oz);
};
