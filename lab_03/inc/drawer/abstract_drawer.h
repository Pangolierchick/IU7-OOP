#pragma once

#include "object/model/details/point/point.h"

class AbstractDrawer {
public:
    AbstractDrawer() = default;

    virtual ~AbstractDrawer() = default;

    virtual void draw_line(const Point& point_1, const Point& point_2) = 0;
    virtual void clear_scene() = 0;
};
